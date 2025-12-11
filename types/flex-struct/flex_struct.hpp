/**
 * @file flex_struct.hpp
 * @authors MarioS271
 */

#pragma once

#include <string>
#include <unordered_map>
#include <freertos/FreeRTOS.h>
#include "logger.hpp"

class FlexStruct {
private:
    std::unordered_map<std::string, void*> resources;
    std::unordered_map<std::string, size_t> sizes;
    SemaphoreHandle_t mutex;

public:
    explicit FlexStruct() {
        mutex = xSemaphoreCreateMutex();
    }

    ~FlexStruct() {
        if (!mutex) return;

        xSemaphoreTake(mutex, portMAX_DELAY);

        for (auto& pair : resources)
            free(pair.second);

        resources.clear();
        sizes.clear();

        xSemaphoreGive(mutex);
        vSemaphoreDelete(mutex);
    }

    /**
     * @brief Sets a value in the flex struct
     *
     * @return (void)  
     *
     * @param key The key of the value to set
     * @param value The value to set
     * 
     * @tparam T The type of the value to store
    */
    template <typename T>
    void set(const std::string& key, const T& value) {
        xSemaphoreTake(mutex, portMAX_DELAY);

        auto it = resources.find(key);
        if (it != resources.end())
            free(it->second);

        T* ptr = (T*) malloc(sizeof(T));
        if (!ptr) {
            LOGE("FlexStruct", "Failed to allocate memory for key '%s'", key.c_str());
            xSemaphoreGive(mutex);
            return;
        }
        *ptr = value;

        resources[key] = ptr;
        sizes[key] = sizeof(T);

        xSemaphoreGive(mutex);
    }

    /**
     * @brief Fetches a value from the flex struct
     *
     * @return (T) The stored value if found and type matches, otherwise `defaultValue`
     *
     * @param key The stringkey of the element to get
     * @param defaultValue The default value to return if nothing is found
     * 
     * @tparam T The type of the value to fetch
     */
    template <typename T>
    T get(const std::string& key, const T& defaultValue = T()) const {
        xSemaphoreTake(mutex, portMAX_DELAY);

        auto it = resources.find(key);
        T result = defaultValue;

        if (it != resources.end() && sizes.at(key) == sizeof(T))
            result = *(T*) (it->second);

        xSemaphoreGive(mutex);
        return result;
    }

    /**
     * @brief Check if the flex struct contains a certain value
     *
     * @return (bool) If the value was found
     *
     * @param key The key to search for
    */
    bool contains(const std::string& key) const {
        xSemaphoreTake(mutex, portMAX_DELAY);
        bool found = (resources.find(key) != resources.end());
        xSemaphoreGive(mutex);
        return found;
    }
};