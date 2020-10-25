#pragma once

#include <vector>

namespace Phoenix
{

	enum class ShaderDataType
	{
		None = 0, Vector, Vector2, Vector3, Vector4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Vector : return 4;
			case ShaderDataType::Vector2: return 4 * 2;
			case ShaderDataType::Vector3: return 4 * 3;
			case ShaderDataType::Vector4: return 4 * 4;
			case ShaderDataType::Mat3   : return 4 * 3 * 3;
			case ShaderDataType::Mat4   : return 4 * 4 * 4;
			case ShaderDataType::Int    : return 4;
			case ShaderDataType::Int2   : return 4 * 2;
			case ShaderDataType::Int3   : return 4 * 3;
			case ShaderDataType::Int4   : return 4 * 4;
			case ShaderDataType::Bool   : return 1;
		}

		PX_CORE_ASSERT(false, "Unknown Shader datatype!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Vector:   return 1;
			case ShaderDataType::Vector2:  return 2;
			case ShaderDataType::Vector3:  return 3;
			case ShaderDataType::Vector4:  return 4;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
			}

			PX_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}