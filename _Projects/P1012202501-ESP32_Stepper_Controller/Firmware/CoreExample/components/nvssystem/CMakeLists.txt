idf_component_register(SRCS "nvssystem.c"
                    INCLUDE_DIRS "."
                    REQUIRES "driver"
                    REQUIRES "freertos"
                    REQUIRES nvs_flash)
