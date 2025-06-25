set(src
        "src/mm_app_loadconfig.cpp"
        "src/mm_app_common.cpp"
        "src/main.cpp")

set(inc
        "src")

idf_component_register(SRCS ${src}
        INCLUDE_DIRS ${inc}
        PRIV_REQUIRES driver morselib mm_shims mmipal lwip esp_timer esp_http_server)
