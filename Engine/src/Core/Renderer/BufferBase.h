#pragma once

namespace Karem {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};
	
	std::shared_ptr<VertexArray> CreateVertexArray();

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};

	//std::shared_ptr<VertexBuffer> CreateVertexBuffer();

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};

	//std::shared_ptr<IndexBuffer> CreateIndexBuffer();

}
