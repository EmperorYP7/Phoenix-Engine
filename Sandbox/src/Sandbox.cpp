#include <Phoenix.hpp>

class ExampleLayer : public Phoenix::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Phoenix::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Phoenix::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Phoenix::VertexBuffer::Create(vertices, sizeof(vertices)));
		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Vector3, "a_Position" },
			{ Phoenix::ShaderDataType::Vector4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Phoenix::IndexBuffer> indexBuffer;
		indexBuffer.reset(Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Phoenix::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Phoenix::VertexBuffer> squareVB;
		squareVB.reset(Phoenix::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Phoenix::ShaderDataType::Vector3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Phoenix::IndexBuffer> squareIB;
		squareIB.reset(Phoenix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_VP;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_VP * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Phoenix::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_VP;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_VP * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Phoenix::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(const Phoenix::Timestep& ts) override
	{
		if (Phoenix::Input::IsKeyPressed(PX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Phoenix::Input::IsKeyPressed(PX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Phoenix::Input::IsKeyPressed(PX_KEY_MINUS) || Phoenix::Input::IsKeyPressed(PX_KEY_KP_SUBTRACT))
			m_CameraPosition.z += m_CameraMoveSpeed * ts;
		else if (Phoenix::Input::IsKeyPressed(PX_KEY_KP_ADD))
			m_CameraPosition.z -= m_CameraMoveSpeed * ts;

		if (Phoenix::Input::IsKeyPressed(PX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Phoenix::Input::IsKeyPressed(PX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Phoenix::Input::IsKeyPressed(PX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Phoenix::Input::IsKeyPressed(PX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Phoenix::RenderCommand::ClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Phoenix::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Phoenix::Renderer::BeginScene(m_Camera);

		Phoenix::Renderer::Submit(m_BlueShader, m_SquareVA);
		Phoenix::Renderer::Submit(m_Shader, m_VertexArray);

		Phoenix::Renderer::EndScene();
	}

	void OnEvent(Phoenix::Event& e) override
	{
		if (e.GetEventType() == Phoenix::EventType::KeyPressed)
		{
			Phoenix::KeyPressedEvent& event = (Phoenix::KeyPressedEvent&)e;
			if (event.GetKeyCode() == PX_KEY_TAB)
				PX_TRACE("Tab key is pressed (event)!");
			PX_TRACE("{0}", (char)event.GetKeyCode());
		}
	}

private:
	std::shared_ptr<Phoenix::Shader> m_Shader;
	std::shared_ptr<Phoenix::VertexArray> m_VertexArray;

	std::shared_ptr<Phoenix::Shader> m_BlueShader;
	std::shared_ptr<Phoenix::VertexArray> m_SquareVA;

	Phoenix::OrthoCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 4.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Phoenix::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Phoenix::Application* Phoenix::CreateApplication()
{
	return new Sandbox();
}