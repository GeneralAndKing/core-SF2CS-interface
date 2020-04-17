//
// Created by bugrui on 2020/3/24.
//

#ifndef CORE_SF2CS_INTERFACE_CONCURRENTMAP_H
#define CORE_SF2CS_INTERFACE_CONCURRENTMAP_H
#include <map>
#include <memory>
#include <mutex>
//thread safe map, need to free data youself
    template<typename TKey, typename TValue>
    class ConcurrentMap
    {
    public:
        ConcurrentMap()
        {
        }

        virtual ~ConcurrentMap()
        {
            std::lock_guard<std::mutex> locker(m_mutexMap);
            m_map.clear();
        }

        bool insert(const TKey &key, const TValue &value, bool cover = false)
        {
            std::lock_guard<std::mutex> locker(m_mutexMap);

            auto find = m_map.find(key);
            if (find != m_map.end() && cover)
            {
                m_map.erase(find);
            }

            auto result = m_map.insert(std::pair<TKey, TValue>(key, value));
            return result.second;
        }

        void remove(const TKey &key)
        {
            std::lock_guard<std::mutex> locker(m_mutexMap);

            auto find = m_map.find(key);
            if (find != m_map.end())
            {
                m_map.erase(find);
            }
        }

        bool lookup(const TKey &key, TValue &value)
        {
            std::lock_guard<std::mutex> locker(m_mutexMap);

            auto find = m_map.find(key);
            if (find != m_map.end())
            {
                value = (*find).second;
                return true;
            }
            else
            {
                return false;
            }
        }

        int size()
        {
            std::lock_guard<std::mutex> locker(m_mutexMap);
            return m_map.size();
        }

    public:
        std::mutex m_mutexMap;
        std::map<TKey, TValue> m_map;
    };
#endif //CORE_SF2CS_INTERFACE_CONCURRENTMAP_H
