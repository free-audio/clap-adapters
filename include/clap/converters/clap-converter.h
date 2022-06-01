#pragma once

#include "../clap.h"
#include "../stream.h"

#ifdef __cplusplus
extern "C" {
#endif

// This interface provides all the tools to convert a clap plugin instance into a clap plugin instance.
typedef struct clap_clap_converter {
   const char *src_plugin_id;
   const char *dst_plugin_id;

   // [main-thread]
   bool (*convert_state)(const struct clap_clap_converter *converter,
                         const clap_istream_t             *src,
                         const clap_ostream_t             *dst);

   // converts the clap param id and normalized value.
   // [thread-safe]
   bool (*convert_normalized_value)(const struct clap_clap_converter *converter,
                                    clap_id                           src_param_id,
                                    double                            src_normalized_value,
                                    clap_id                          *dst_param_id,
                                    double                           *dst_normalized_value);

   // converts the clap param id and plain value.
   // [thread-safe]
   bool (*convert_plain_value)(const struct clap_clap_converter *converter,
                               clap_id                           src_param_id,
                               double                            src_plain_value,
                               clap_id                          *dst_param_id,
                               double                           *dst_plain_value);
} clap_clap_converter_t;

// Factory identifier
static CLAP_CONSTEXPR const char CLAP_CLAP_CONVERTER_FACTORY_ID[] = "clap.clap-converter-factory/draft0";

// List all the converters available in the current DSO.
typedef struct clap_clap_converter_factory {
   // Get the number of converters
   uint32_t (*count)(const struct clap_clap_converter_factory *factory);

   // Get the converter at the given index
   const clap_clap_converter_t *(*get)(const struct clap_clap_converter_factory *factory,
                                       uint32_t                                  index);
} clap_clap_converter_factory_t;

#ifdef __cplusplus
}
#endif
