//
// Copyright (c) 2017 The Khronos Group Inc.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "../../test_common/harness/compat.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../../test_common/harness/testHarness.h"
#include "../../test_common/harness/errorHelpers.h"
#include "../../test_common/harness/kernelHelpers.h"

static int dump_supported_formats;

typedef struct
{
    cl_device_type device_type;
    const char*    device_type_name;
    unsigned       num_devices;
    cl_device_id*  devices;
    // more infos here
} device_info;

device_info device_infos[] =
{
    {CL_DEVICE_TYPE_DEFAULT,     "CL_DEVICE_TYPE_DEFAULT",     -1, NULL},
    {CL_DEVICE_TYPE_CPU,         "CL_DEVICE_TYPE_CPU",         -1, NULL},
    {CL_DEVICE_TYPE_GPU,         "CL_DEVICE_TYPE_GPU",         -1, NULL},
    {CL_DEVICE_TYPE_ACCELERATOR, "CL_DEVICE_TYPE_ACCELERATOR", -1, NULL},
    {CL_DEVICE_TYPE_ALL,         "CL_DEVICE_TYPE_ALL",         -1, NULL},
};

// config types
enum
{
    type_cl_device_type,
    type_cl_device_fp_config,
    type_cl_device_mem_cache_type,
    type_cl_local_mem_type,
    type_cl_device_exec_capabilities,
    type_cl_command_queue_properties,
    type_cl_device_id,
    type_cl_device_affinity_domain,
    type_cl_uint,
    type_size_t,
    type_size_t_arr,
    type_cl_ulong,
    type_string,
    type_cl_device_svm_capabilities,
};

typedef union
{
    cl_device_type                  type;
    cl_device_fp_config             fp_config;
    cl_device_mem_cache_type        mem_cache_type;
    cl_device_local_mem_type        local_mem_type;
    cl_device_exec_capabilities     exec_capabilities;
    cl_command_queue_properties     queue_properties;
    cl_device_id                    device_id;
    cl_device_affinity_domain       affinity_domain;
    cl_int                          uint;
    size_t                          sizet;
    size_t                          sizet_arr[3];
    cl_ulong                        ull;
    char                            string[1024];
    cl_device_svm_capabilities      svmCapabilities;
} config_data;

struct _version {
  int major;
  int minor;
};
typedef struct _version version_t;

struct _extensions {
  int cl_khr_fp64;
  int cl_khr_fp16;
};
typedef struct _extensions extensions_t;

// Compare two versions, return -1 (the first is lesser), 0 (equal), 1 (the first is greater).
int vercmp( version_t a, version_t b ) {
  if ( a.major < b.major || a.major == b.major && a.minor < b.minor ) {
    return -1;
  } else if ( a.major == b.major && a.minor == b.minor ) {
    return 0;
  } else {
    return 1;
  }
}

typedef struct
{
    version_t             version;    // Opcode is introduced in this version of OpenCL spec.
    cl_device_info        opcode;
    const char*           opcode_name;
    int                   config_type;
    config_data           config;
} config_info;

#define CONFIG_INFO( major, minor, opcode, type ) { { major, minor }, opcode, #opcode, type_ ## type, { 0 } }

config_info image_buffer_config_infos[] =
{
#ifdef CL_DEVICE_IMAGE_PITCH_ALIGNMENT
    CONFIG_INFO( 1, 2, CL_DEVICE_IMAGE_PITCH_ALIGNMENT, cl_uint),
    CONFIG_INFO( 1, 2, CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT, cl_uint),
#endif
};

config_info config_infos[] =
{
    // `CL_DEVICE_VERSION' must be the first item in the list! It's version must be 0, 0.
    CONFIG_INFO( 0, 0, CL_DEVICE_VERSION, string),
    // `CL_DEVICE_EXTENSIONS' must be the second!
    CONFIG_INFO( 1, 1, CL_DEVICE_EXTENSIONS, string),

    CONFIG_INFO( 1, 1, CL_DEVICE_TYPE, cl_device_type),
    CONFIG_INFO( 1, 1, CL_DEVICE_VENDOR_ID, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_COMPUTE_UNITS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_WORK_ITEM_SIZES, size_t_arr),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_WORK_GROUP_SIZE, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, cl_uint),

    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_CLOCK_FREQUENCY, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_ADDRESS_BITS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_READ_IMAGE_ARGS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_WRITE_IMAGE_ARGS, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_MEM_ALLOC_SIZE, cl_ulong),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE2D_MAX_WIDTH, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE2D_MAX_HEIGHT, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE3D_MAX_WIDTH, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE3D_MAX_HEIGHT, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE3D_MAX_DEPTH, size_t),
    CONFIG_INFO( 1, 2, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, size_t),
    CONFIG_INFO( 1, 2, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_IMAGE_SUPPORT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_PARAMETER_SIZE, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_SAMPLERS, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_IMAGE_PITCH_ALIGNMENT, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT, cl_uint),

    CONFIG_INFO( 1, 1, CL_DEVICE_MEM_BASE_ADDR_ALIGN, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_SINGLE_FP_CONFIG, cl_device_fp_config),
    CONFIG_INFO( 1, 1, CL_DEVICE_DOUBLE_FP_CONFIG, cl_device_fp_config),
    CONFIG_INFO( 1, 1, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, cl_device_mem_cache_type),
    CONFIG_INFO( 1, 1, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, cl_ulong),
    CONFIG_INFO( 1, 1, CL_DEVICE_GLOBAL_MEM_SIZE, cl_ulong),

    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, cl_ulong),
    CONFIG_INFO( 1, 1, CL_DEVICE_MAX_CONSTANT_ARGS, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_LOCAL_MEM_TYPE, cl_local_mem_type),
    CONFIG_INFO( 1, 1, CL_DEVICE_LOCAL_MEM_SIZE, cl_ulong),
    CONFIG_INFO( 1, 1, CL_DEVICE_ERROR_CORRECTION_SUPPORT, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_HOST_UNIFIED_MEMORY, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_PROFILING_TIMER_RESOLUTION, size_t),
    CONFIG_INFO( 1, 1, CL_DEVICE_ENDIAN_LITTLE, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_AVAILABLE, cl_uint),
    CONFIG_INFO( 1, 1, CL_DEVICE_COMPILER_AVAILABLE, cl_uint),
    CONFIG_INFO( 1, 2, CL_DEVICE_LINKER_AVAILABLE, cl_uint),

    CONFIG_INFO( 1, 2, CL_DEVICE_BUILT_IN_KERNELS, string),

    CONFIG_INFO( 1, 2, CL_DEVICE_PRINTF_BUFFER_SIZE, size_t),
    CONFIG_INFO( 1, 2, CL_DEVICE_PREFERRED_INTEROP_USER_SYNC, cl_uint),

    CONFIG_INFO( 1, 2, CL_DEVICE_PARENT_DEVICE, cl_device_id),
    CONFIG_INFO( 1, 2, CL_DEVICE_PARTITION_MAX_SUB_DEVICES, cl_uint),
    CONFIG_INFO( 1, 2, CL_DEVICE_PARTITION_AFFINITY_DOMAIN, cl_device_affinity_domain),
    CONFIG_INFO( 1, 2, CL_DEVICE_REFERENCE_COUNT, cl_uint),

    CONFIG_INFO( 1, 1, CL_DEVICE_EXECUTION_CAPABILITIES, cl_device_exec_capabilities),
    CONFIG_INFO( 1, 1, CL_DEVICE_QUEUE_ON_HOST_PROPERTIES, cl_command_queue_properties),
    CONFIG_INFO( 1, 1, CL_DEVICE_NAME, string),
    CONFIG_INFO( 1, 1, CL_DEVICE_VENDOR, string),
    CONFIG_INFO( 1, 1, CL_DRIVER_VERSION, string),
    CONFIG_INFO( 1, 1, CL_DEVICE_PROFILE, string),
    CONFIG_INFO( 1, 1, CL_DEVICE_VERSION, string),
    CONFIG_INFO( 1, 1, CL_DEVICE_OPENCL_C_VERSION, string),
    CONFIG_INFO( 1, 1, CL_DEVICE_EXTENSIONS, string),

    CONFIG_INFO( 2, 0, CL_DEVICE_MAX_PIPE_ARGS, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_PIPE_MAX_PACKET_SIZE, cl_uint),

    CONFIG_INFO( 2, 0, CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE, size_t),
    CONFIG_INFO( 2, 0, CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE, size_t),

    CONFIG_INFO( 2, 0, CL_DEVICE_QUEUE_ON_HOST_PROPERTIES, cl_command_queue_properties),
    CONFIG_INFO( 2, 0, CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES, cl_command_queue_properties),
    CONFIG_INFO( 2, 0, CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_MAX_ON_DEVICE_QUEUES, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_MAX_ON_DEVICE_EVENTS, cl_uint),

    CONFIG_INFO( 2, 0, CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT, cl_uint),
    CONFIG_INFO( 2, 0, CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT , cl_uint),

    CONFIG_INFO( 2, 0, CL_DEVICE_SVM_CAPABILITIES, cl_device_svm_capabilities),
};

#define ENTRY(T) { T, #T }
struct image_type_entry {
    cl_mem_object_type val;
    const char *str;
};
static const struct image_type_entry image_types[] = {
    ENTRY(CL_MEM_OBJECT_IMAGE1D), ENTRY(CL_MEM_OBJECT_IMAGE1D_BUFFER),
    ENTRY(CL_MEM_OBJECT_IMAGE2D), ENTRY(CL_MEM_OBJECT_IMAGE3D),
    ENTRY(CL_MEM_OBJECT_IMAGE1D_ARRAY), ENTRY(CL_MEM_OBJECT_IMAGE2D_ARRAY)
};

struct supported_flags_entry {
    cl_mem_flags val;
    const char *str;
};

static const struct supported_flags_entry supported_flags[] = {
    ENTRY(CL_MEM_READ_ONLY), ENTRY(CL_MEM_WRITE_ONLY),
    ENTRY(CL_MEM_READ_WRITE), ENTRY(CL_MEM_KERNEL_READ_AND_WRITE)
};

int getImageInfo(cl_device_id device)
{
    cl_context ctx;
    cl_int err;
    cl_uint i, num_supported;
    cl_image_format *formats;
    int num_errors;
    int ii, ni = sizeof(image_types)/sizeof(image_types[0]);
    int fi, nf = sizeof(supported_flags)/sizeof(supported_flags[0]);

    ctx = clCreateContext(NULL, 1, &device, notify_callback, NULL, &err);
    if (!ctx) {
        print_error(err, "Unable to create context from device");
        return 1;
    }

    num_errors = 0;
    for (ii=0; ii<ni; ++ii) {
        log_info("\t%s supported formats:\n", image_types[ii].str);
        for (fi=0; fi<nf; ++fi) {

            err = clGetSupportedImageFormats(ctx, supported_flags[fi].val, image_types[ii].val, 5000, NULL, &num_supported);
            if (err != CL_SUCCESS) {
                print_error(err, "clGetSupportedImageFormats failed");
                ++num_errors;
                continue;
            }

            log_info("\t\t%s: %u supported formats\n", supported_flags[fi].str, num_supported);

            if (num_supported == 0 || dump_supported_formats == 0)
                continue;

            formats = (cl_image_format *)malloc(num_supported * sizeof(cl_image_format));
            if (formats == NULL) {
                log_error("malloc failed\n");
                clReleaseContext(ctx);
                return num_errors + 1;
            }

            err = clGetSupportedImageFormats(ctx, supported_flags[fi].val, image_types[ii].val, num_supported, formats, NULL);
            if (err != CL_SUCCESS) {
                print_error(err, "clGetSupportedImageFormats failed");
                ++num_errors;
                free(formats);
                continue;
            }

            for (i=0; i<num_supported; ++i)
                log_info("\t\t\t%s / %s\n",
                         GetChannelOrderName(formats[i].image_channel_order),
                         GetChannelTypeName(formats[i].image_channel_data_type));

            free(formats);
        }
    }

    err = clReleaseContext(ctx);
    if (err) {
        print_error(err, "Failed to release context\n");
        ++num_errors;
    }

    return num_errors;
}

int getConfigInfo(cl_device_id device, config_info* info)
{
    int err = CL_SUCCESS;
    int size_err = 0;
    size_t config_size_ret;
    switch(info->config_type)
    {
        case type_cl_device_type:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.type), &info->config.type, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.type);
            break;
        case type_cl_device_fp_config:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.fp_config), &info->config.fp_config, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.fp_config);
            break;
        case type_cl_device_mem_cache_type:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.mem_cache_type), &info->config.mem_cache_type, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.mem_cache_type);
            break;
        case type_cl_local_mem_type:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.local_mem_type), &info->config.local_mem_type, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.local_mem_type);
            break;
        case type_cl_device_exec_capabilities:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.exec_capabilities), &info->config.exec_capabilities, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.exec_capabilities);
            break;
        case type_cl_command_queue_properties:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.queue_properties), &info->config.queue_properties, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.queue_properties);
            break;
        case type_cl_device_id:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.device_id), &info->config.device_id, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.device_id);
            break;
        case type_cl_device_affinity_domain:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.affinity_domain), &info->config.affinity_domain, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.affinity_domain);
            break;
        case type_cl_uint:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.uint), &info->config.uint, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.uint);
            break;
        case type_size_t_arr:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.sizet_arr), &info->config.sizet_arr, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.sizet_arr);
            break;
        case type_size_t:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.sizet), &info->config.sizet, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.sizet);
            break;
        case type_cl_ulong:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.ull), &info->config.ull, &config_size_ret);
            size_err = config_size_ret != sizeof(info->config.ull);
            break;
        case type_string:
            err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.string), &info->config.string, &config_size_ret);
            break;
        case type_cl_device_svm_capabilities:
          err = clGetDeviceInfo(device, info->opcode, sizeof(info->config.svmCapabilities), &info->config.svmCapabilities, &config_size_ret);
          break;
        default:
            log_error("Unknown config type: %d\n", info->config_type);
            break;
    }
    if (err || size_err)
        log_error("\tFailed clGetDeviceInfo for %s.\n", info->opcode_name);
    if(err)
        print_error(err, "\t\tclGetDeviceInfo failed.");
    if (size_err)
        log_error("\t\tWrong size return from clGetDeviceInfo.\n");
    return err || size_err;
}

void dumpConfigInfo(cl_device_id device, config_info* info)
{
    // We should not error if we find an unknown configuration since vendors
    // may specify their own options beyond the list in the specification.
    switch(info->config_type)
    {
        case type_cl_device_type:
            log_info("\t%s == %s|%s|%s|%s\n", info->opcode_name,
                     (info->config.fp_config & CL_DEVICE_TYPE_CPU) ? "CL_DEVICE_TYPE_CPU":"",
                     (info->config.fp_config & CL_DEVICE_TYPE_GPU) ? "CL_DEVICE_TYPE_GPU":"",
                     (info->config.fp_config & CL_DEVICE_TYPE_ACCELERATOR) ? "CL_DEVICE_TYPE_ACCELERATOR":"",
                     (info->config.fp_config & CL_DEVICE_TYPE_DEFAULT) ? "CL_DEVICE_TYPE_DEFAULT":""
                     );
            {
                cl_device_type all_device_types = CL_DEVICE_TYPE_CPU | CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_ACCELERATOR | CL_DEVICE_TYPE_DEFAULT;
                if(info->config.fp_config & ~all_device_types)
                {
                    log_info("WARNING: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.fp_config & ~all_device_types));
                }
            }
            break;
        case type_cl_device_fp_config:
            log_info("\t%s == %s|%s|%s|%s|%s|%s|%s\n", info->opcode_name,
                     (info->config.fp_config & CL_FP_DENORM) ? "CL_FP_DENORM":"",
                     (info->config.fp_config & CL_FP_INF_NAN) ? "CL_FP_INF_NAN":"",
                     (info->config.fp_config & CL_FP_ROUND_TO_NEAREST) ? "CL_FP_ROUND_TO_NEAREST":"",
                     (info->config.fp_config & CL_FP_ROUND_TO_ZERO) ? "CL_FP_ROUND_TO_ZERO":"",
                     (info->config.fp_config & CL_FP_ROUND_TO_INF) ? "CL_FP_ROUND_TO_INF":"",
                     (info->config.fp_config & CL_FP_FMA) ? "CL_FP_FMA":"",
                     (info->config.fp_config & CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT) ? "CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT":""
                     );
            {
                cl_device_fp_config all_fp_config = CL_FP_DENORM | CL_FP_INF_NAN | CL_FP_ROUND_TO_NEAREST |
                                                    CL_FP_ROUND_TO_ZERO | CL_FP_ROUND_TO_INF | CL_FP_FMA |
                                                    CL_FP_CORRECTLY_ROUNDED_DIVIDE_SQRT;
                if(info->config.fp_config & ~all_fp_config)
                    log_info("WARNING: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.fp_config & ~all_fp_config));
            }
            break;
        case type_cl_device_mem_cache_type:
            switch(info->config.mem_cache_type)
            {
                case CL_NONE:
                    log_info("\t%s == CL_NONE\n", info->opcode_name);
                    break;
                case CL_READ_ONLY_CACHE:
                    log_info("\t%s == CL_READ_ONLY_CACHE\n", info->opcode_name);
                    break;
                case CL_READ_WRITE_CACHE:
                    log_info("\t%s == CL_READ_WRITE_CACHE\n", info->opcode_name);
                    break;
                default:
                    log_error("ERROR: %s out of range, %d\n", info->opcode_name, info->config.mem_cache_type);
                    break;
            }
            break;
        case type_cl_local_mem_type:
            switch(info->config.local_mem_type)
            {
                case CL_NONE:
                    log_info("\t%s == CL_NONE\n", info->opcode_name);
                    break;
                case CL_LOCAL:
                    log_info("\t%s == CL_LOCAL\n", info->opcode_name);
                    break;
                case CL_GLOBAL:
                    log_info("\t%s == CL_GLOBAL\n", info->opcode_name);
                    break;
                default:
                    log_info("WARNING: %s out of range, %d\n", info->opcode_name, info->config.local_mem_type);
                    break;
            }
            break;
        case type_cl_device_exec_capabilities:
            log_info("\t%s == %s|%s\n", info->opcode_name,
                     (info->config.exec_capabilities & CL_EXEC_KERNEL) ? "CL_EXEC_KERNEL":"",
                     (info->config.exec_capabilities & CL_EXEC_NATIVE_KERNEL) ? "CL_EXEC_NATIVE_KERNEL":"" );
            {
                cl_device_exec_capabilities all_exec_cap = CL_EXEC_KERNEL | CL_EXEC_NATIVE_KERNEL;
                if(info->config.exec_capabilities & ~all_exec_cap)
                    log_info("WARNING: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.exec_capabilities & ~all_exec_cap));
            }
            break;
        case type_cl_command_queue_properties:
            log_info("\t%s == %s|%s\n", info->opcode_name,
                     (info->config.queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) ? "CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE":"",
                     (info->config.queue_properties & CL_QUEUE_PROFILING_ENABLE) ? "CL_QUEUE_PROFILING_ENABLE":"");
            {
                cl_command_queue_properties all_queue_properties = CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE;
                if(info->config.queue_properties & ~all_queue_properties)
                    log_info("WARNING: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.exec_capabilities & ~all_queue_properties));
            }
            break;
        case type_cl_device_id:
            log_info("\t%s == %ld\n", info->opcode_name, (intptr_t)info->config.device_id);
            break;
        case type_cl_device_affinity_domain:
            log_info("\t%s == %s|%s|%s|%s|%s|%s\n", info->opcode_name,
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_NUMA) ? "CL_DEVICE_AFFINITY_DOMAIN_NUMA":"",
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE) ? "CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE":"",
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE) ? "CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE":"",
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE) ? "CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE":"",
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE) ? "CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE":"",
                     (info->config.affinity_domain & CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE) ? "CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE":""
                     );
            {
                cl_device_affinity_domain all_affinity_domain = CL_DEVICE_AFFINITY_DOMAIN_NUMA |
                                                                CL_DEVICE_AFFINITY_DOMAIN_L4_CACHE |
                                                                CL_DEVICE_AFFINITY_DOMAIN_L3_CACHE |
                                                                CL_DEVICE_AFFINITY_DOMAIN_L2_CACHE |
                                                                CL_DEVICE_AFFINITY_DOMAIN_L1_CACHE |
                                                                CL_DEVICE_AFFINITY_DOMAIN_NEXT_PARTITIONABLE;
                if(info->config.affinity_domain & ~all_affinity_domain)
                    log_error("ERROR: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.affinity_domain & ~all_affinity_domain));
            }
            break;
        case type_cl_uint:
            log_info("\t%s == %u\n", info->opcode_name, info->config.uint);
            break;
        case type_size_t_arr:
            log_info("\t%s == %d %d %d\n", info->opcode_name, info->config.sizet_arr[0],
                     info->config.sizet_arr[1], info->config.sizet_arr[2]);
            break;
        case type_size_t:
            log_info("\t%s == %ld\n", info->opcode_name, info->config.sizet);
            break;
        case type_cl_ulong:
            log_info("\t%s == %lld\n", info->opcode_name, info->config.ull);
            break;
        case type_string:
            log_info("\t%s == \"%s\"\n", info->opcode_name, info->config.string);
            break;
        case type_cl_device_svm_capabilities:
          log_info("\t%s == %s|%s|%s|%s\n", info->opcode_name,
            (info->config.svmCapabilities & CL_DEVICE_SVM_COARSE_GRAIN_BUFFER) ? "CL_DEVICE_SVM_COARSE_GRAIN_BUFFER":"",
            (info->config.svmCapabilities & CL_DEVICE_SVM_FINE_GRAIN_BUFFER) ? "CL_DEVICE_SVM_FINE_GRAIN_BUFFER":"",
            (info->config.svmCapabilities & CL_DEVICE_SVM_FINE_GRAIN_SYSTEM) ? "CL_DEVICE_SVM_FINE_GRAIN_SYSTEM":"",
            (info->config.svmCapabilities & CL_DEVICE_SVM_ATOMICS) ? "CL_DEVICE_SVM_ATOMICS":"");
          {
            cl_device_svm_capabilities all_svm_capabilities = CL_DEVICE_SVM_COARSE_GRAIN_BUFFER |
                                                              CL_DEVICE_SVM_FINE_GRAIN_BUFFER |
                                                              CL_DEVICE_SVM_FINE_GRAIN_SYSTEM |
                                                              CL_DEVICE_SVM_ATOMICS;
            if(info->config.svmCapabilities & ~all_svm_capabilities)
              log_info("WARNING: %s unknown bits found 0x%08llX", info->opcode_name, (info->config.svmCapabilities & ~all_svm_capabilities));
          }
          break;
    }
}

void print_platform_string_selector( cl_platform_id platform, const char *selector_name, cl_platform_info selector )
{
    // Currently all the selectors are strings
    size_t size = 0;
    char *value;
    int err;

    if(( err = clGetPlatformInfo( platform, selector, 0, NULL, &size )))
    {
        log_error( "FAILURE: Unable to get platform info size for %s.\n", selector_name );
        exit( -1 );
    }

    if( size == 0 )
    {
        log_error( "FAILURE: The size of %s was returned to be zero.\n", selector_name );
        exit( -1 );
    }

    value = (char*) malloc( size );
    if( NULL == value )
    {
        log_error( "Internal test failure:  Unable to allocate %ld bytes\n", size );
        exit(-1);
    }

    memset( value, -1, size );
    if(( err = clGetPlatformInfo( platform, selector, size, value, NULL )))
    {
        log_error( "FAILURE: Unable to get platform info for %s.\n", selector_name );
        free( value );
        exit( -1 );
    }

    if( value[size-1] != '\0' )
    {
        log_error( "FAILURE: platform info for %s is either not NUL terminated, or the size is wrong.\n", selector_name );
        free( value );
        exit( -1 );
    }

    log_info( "\t%s: %s\n", selector_name, value );
    free( value );
}

int parseVersion( char const * str, version_t * version )
{
  int rc = -1;
  version->major = 0;
  version->minor = 0;
  if ( strncmp( str, "OpenCL 1.2", 10 ) == 0 && ( str[ 10 ] == 0 || str[ 10 ] == ' ' ) ) {
    version->major = 1;
    version->minor = 2;
    rc = 0;
  } else if ( strncmp( str, "OpenCL 1.1", 10 ) == 0 && ( str[ 10 ] == 0 || str[ 10 ] == ' ' ) ) {
    version->major = 1;
    version->minor = 1;
    rc = 0;
  } else if ( strncmp( str, "OpenCL 2.0", 10 ) == 0 && ( str[ 10 ] == 0 || str[ 10 ] == ' ' ) ) {
    version->major = 2;
    version->minor = 0;
    rc = 0;
  } else if ( strncmp( str, "OpenCL 2.1", 10 ) == 0 && ( str[ 10 ] == 0 || str[ 10 ] == ' ' ) ) {
    version->major = 2;
    version->minor = 1;
    rc = 0;
  } else {
    log_error( "ERROR: Unexpected version string: `%s'.\n", str );
  };
  return rc;
}

int parseExtensions( char const * str, extensions_t * extensions )
{
  char const * begin  = NULL;
  char const * space  = NULL;
  size_t       length = 0;

  memset( extensions, 0, sizeof ( extensions_t ) );

  begin = str;
  while ( begin[ 0 ] != 0 ) {
    space = strchr( begin, ' ' );    // Find space position.
    if ( space != NULL ) {           // Calculate length of word.
      length = space - begin;
    } else {
      length = strlen( begin );
    }
    if ( strncmp( begin, "cl_khr_fp64", length ) == 0 ) {
      extensions->cl_khr_fp64 = 1;
    }
    if ( strncmp( begin, "cl_khr_fp16", length ) == 0 ) {
      extensions->cl_khr_fp16 = 1;
    }
    begin += length;                 // Skip word.
    if ( begin[ 0 ] == ' ' ) {       // Skip space, if any.
      begin += 1;
    }
  }

  return 0;
}

int getConfigInfos( cl_device_id device )
{
  int             total_errors = 0;
  unsigned        onConfigInfo;
  version_t       version = { 0, 0 }; // Version of the device. Will get real value on the first loop iteration.
  version_t const ver11   = { 1, 1 }; // Version 1.1.
  extensions_t    extensions = { 0 };
  int             get;                // Boolean flag: true = get property, false = skip it.
  int             err;
  for ( onConfigInfo = 0; onConfigInfo < sizeof(config_infos) / sizeof(config_infos[0]); onConfigInfo++) {
    config_info info = config_infos[ onConfigInfo ];
    // Get a property only if device version is equal or greater than property version.
    get = ( vercmp( version, info.version ) >= 0 );
    if ( info.opcode == CL_DEVICE_DOUBLE_FP_CONFIG && vercmp( version, ver11 ) <= 0 ) {
      // CL_DEVICE_DOUBLE_FP_CONFIG is a special case. It was introduced in OpenCL 1.1, but
      // device is required to report it only if doubles are supported. So, before querying
      // it on device version 1.1, we have to check doubles are sopported.
      // In OpenCL 1.2 CL_DEVICE_DOUBLE_FP_CONFIG should be reported unconditionally.
      get = extensions.cl_khr_fp64;
    };
    if ( info.opcode == CL_DEVICE_HALF_FP_CONFIG ) {
      // CL_DEVICE_HALF_FP_CONFIG should be reported only when cl_khr_fp16 extension is available
      get = extensions.cl_khr_fp16;
    };
    if ( get ) {
      err = getConfigInfo(device, & info);
      if ( ! err ) {
        dumpConfigInfo(device, & info);
        if ( info.opcode == CL_DEVICE_VERSION ) {
          err = parseVersion( info.config.string, & version );
          if ( err ) {
            total_errors++;
            break;
          }
        } else if ( info.opcode == CL_DEVICE_EXTENSIONS ) {
          err = parseExtensions( info.config.string, & extensions );
          if ( err ) {
            total_errors++;
            break;
          }
        }
      } else {
        total_errors++;
      }
    } else {
      log_info( "\tSkipped: %s.\n", info.opcode_name );
    }
  }

  if (is_extension_available(device, "cl_khr_image2d_from_buffer")){
    for ( onConfigInfo = 0; onConfigInfo < sizeof(image_buffer_config_infos) / sizeof(image_buffer_config_infos[0]); onConfigInfo++) {
      config_info info = image_buffer_config_infos[ onConfigInfo ];
      get = ( vercmp( version, info.version ) >= 0 );
      if ( get ) {
        err = getConfigInfo(device, & info);
        if ( ! err ) {
          dumpConfigInfo(device, & info);
        }
        else {
          total_errors++;
        }
      }
    }
  }

  total_errors += getImageInfo(device);

  return total_errors;
}


int main(int argc, const char** argv)
{
    cl_platform_id platform;
    test_start();

    if (argc == 2) {
    if (!strcmp(argv[1], "-v"))
        dump_supported_formats = 1;
    else {
        log_info("Use option \"-v\" for verbose output\n");
        return 0;
    }
    }

    int err;
    int total_errors = 0;

    err = clGetPlatformIDs(1, &platform, NULL);
    test_error(err, "clGetPlatformIDs failed");
    if (err != CL_SUCCESS) {
        total_errors++;
    }

    // print platform info
    log_info( "\nclGetPlatformInfo:\n------------------\n" );
    print_platform_string_selector( platform, "CL_PLATFORM_PROFILE", CL_PLATFORM_PROFILE );
    print_platform_string_selector( platform, "CL_PLATFORM_VERSION", CL_PLATFORM_VERSION );
    print_platform_string_selector( platform, "CL_PLATFORM_NAME", CL_PLATFORM_NAME );
    print_platform_string_selector( platform, "CL_PLATFORM_VENDOR", CL_PLATFORM_VENDOR );
    print_platform_string_selector( platform, "CL_PLATFORM_EXTENSIONS", CL_PLATFORM_EXTENSIONS );
    log_info( "\n" );

    // Check to see if this test is being run on a specific device
    char* device_type_env = getenv("CL_DEVICE_TYPE");
    char* device_index_env = getenv("CL_DEVICE_INDEX");

    if (device_type_env || device_index_env) {

      cl_device_type device_type = CL_DEVICE_TYPE_DEFAULT;
      size_t device_type_idx = 0;
      size_t device_index = 0;

      // Check to see if a device type was specified.
      if (device_type_env) {
        if (!strcmp(device_type_env,"default") || !strcmp(device_type_env,"CL_DEVICE_TYPE_DEFAULT")) {
          device_type = CL_DEVICE_TYPE_DEFAULT;
          device_type_idx = 0;
        }
        else if (!strcmp(device_type_env,"cpu") || !strcmp(device_type_env,"CL_DEVICE_TYPE_CPU")) {
          device_type = CL_DEVICE_TYPE_CPU;
          device_type_idx = 1;
        }
        else if (!strcmp(device_type_env,"gpu") || !strcmp(device_type_env,"CL_DEVICE_TYPE_GPU")) {
          device_type = CL_DEVICE_TYPE_GPU;
          device_type_idx = 2;
        }
        else if (!strcmp(device_type_env,"accelerator") || !strcmp(device_type_env,"CL_DEVICE_TYPE_ACCELERATOR")) {
          device_type = CL_DEVICE_TYPE_ACCELERATOR;
          device_type_idx = 3;
        }
        else {
          log_error("CL_DEVICE_TYPE=\"%s\" is invalid\n",device_type_env);
          return -1;
        }
      }

      // Check to see if a device index was specified
      if (device_index_env)
        device_index = atoi(device_index_env);

      // Look up the device
      cl_uint num_devices;
      err = clGetDeviceIDs(platform, device_type, 0, NULL, &num_devices);
      if (err)
      {
        log_error("No devices of type %s found.\n", device_type_env);
        return -1;
      }

      if (device_index >= num_devices) {
        log_error("CL_DEVICE_INDEX=%d is greater than the number of matching devices %d\n",(unsigned)device_index,num_devices);
        return -1;
      }

      if (num_devices == 0)
      {
        log_error("No devices of type %s found.\n", device_type_env);
        return -1;
      }

      cl_device_id *devices = (cl_device_id *) malloc( num_devices * sizeof( cl_device_id ) );
      err = clGetDeviceIDs(platform, device_type, num_devices, devices, NULL);
      if (err)
      {
        log_error("No devices of type %s found.\n", device_type_env);
        free(devices);
        return -1;
      }

      cl_device_id device = devices[device_index];
      free(devices);

      log_info("%s Device %d of %d Info:\n", device_infos[device_type_idx].device_type_name, (unsigned)device_index+1, num_devices);
      total_errors += getConfigInfos( device );
      log_info("\n");

    }

    // Otherwise iterate over all of the devices in the platform
    else {
      //print device info
      int onInfo;
      for(onInfo = 0; onInfo < sizeof(device_infos) / sizeof(device_infos[0]); onInfo++)
      {
          log_info("Getting device IDs for %s devices\n", device_infos[onInfo].device_type_name);
          err = clGetDeviceIDs(platform, device_infos[onInfo].device_type, 0, NULL, &device_infos[onInfo].num_devices);
          if (err == CL_DEVICE_NOT_FOUND)
          {
              log_info("No devices of type %s found.\n", device_infos[onInfo].device_type_name);
              continue;
          }
          test_error(err, "clGetDeviceIDs failed");

          log_info("Found %d %s devices:\n", device_infos[onInfo].num_devices, device_infos[onInfo].device_type_name);
          if(device_infos[onInfo].num_devices)
          {
              device_infos[onInfo].devices = (cl_device_id *)malloc(sizeof(cl_device_id) * device_infos[onInfo].num_devices);
              err = clGetDeviceIDs(platform, device_infos[onInfo].device_type, device_infos[onInfo].num_devices, device_infos[onInfo].devices, NULL);
              test_error(err, "clGetDeviceIDs failed");
          }

          int onDevice;
          for(onDevice = 0; onDevice < device_infos[onInfo].num_devices; onDevice++)
          {
              log_info("%s Device %d of %d Info:\n", device_infos[onInfo].device_type_name, onDevice+1, device_infos[onInfo].num_devices);
              total_errors += getConfigInfos( device_infos[onInfo].devices[onDevice] );
              log_info("\n");
          }

          if(device_infos[onInfo].num_devices)
          {
              free(device_infos[onInfo].devices);
          }
      }
    }

    if (total_errors)
        log_error("FAILED computeinfo.\n");
    else
        log_info("PASSED computeinfo.\n");

    test_finish();
    if (total_errors)
        return -1;
    return 0;
}

