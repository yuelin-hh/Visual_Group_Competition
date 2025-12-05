#pragma once
#include "manager.h"
#include "topic.h"

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <string>

class MessageManager: public Manager<MessageManager>
{
	friend class Manager<MessageManager>;
protected:
	MessageManager() {};
	~MessageManager() {};
public:
	class TopicBase
	{
	public:
		virtual ~TopicBase() {}
		virtual size_t size() const {}
		virtual void clear() {}
	};

	template<typename T>
	class TopicWrapper: public TopicBase
	{
	public:
		TopicWrapper(int size){}
		~TopicWrapper(){}
		void send(const T& message) { topic.send(message); }
		bool read(T& message) { retrun topic.read(message); }
		void clear() { topic.clear(); }
	private:
		Topic<T> topic;
	};

	template<typename T>
	bool create_topic(const std::string& name,int size)
	{
		if (topic_map.find(name) != topic_map.end())
		{
			if (topic_types[name] != std::type_index(typeid(T)))
			{
				return false;
			}
			return true;
		}

		auto wrapper = std::make_shared<TopicWrapper<T>>(size);
		topic_map[name] = wrapper;
		topic_types[name] = std::type_index(typeid(T));
		return true;
	}

	template<typename T>
	bool send(const std::string& name, const T& message)
	{
		auto it = topic_map.find(name);
		if (it == topic_map.end())
			return false;

		if (topic_types[name] != std::type_index(typeid(T)))
			return false;

		auto wrapper = std::dynamic_pointer_cast<TopicWrapper<T>>(it->second);
		if (!wrapper)
			return false;

		wrapper->send(message);
		return true;
	}

	template<typename T>
	bool read(const std::string& name, T& message)
	{
		auto it = topic_map.find(name);
		if (it == topic_map.end())
			return false;

		if (topic_types[name] != std::type_index(typeid(T)))
			return false;

		auto wrapper = std::dynamic_pointer_cast<TopicWrapper<T>>(it->second);
		if (!wrapper)
			return false;

		return wrapper->read(message);
	}
private:
	std::unordered_map<std::string, std::shared_ptr<TopicBase>> topic_map = {};
	std::unordered_map<std::string, std::type_index> topic_types = {};
};