// Copyright 2021-present StarRocks, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <string>

#include "common/status.h"

namespace starrocks {
class CloudCredential {
public:
    virtual ~CloudCredential() = default;
};

class AWSCloudCredential final : public CloudCredential {
public:
    bool use_aws_sdk_default_behavior;
    bool use_instance_profile;
    std::string access_key;
    std::string secret_key;
    std::string session_token;
    std::string iam_role_arn;
    std::string sts_region;
    std::string sts_endpoint;
    std::string external_id;
    std::string region;
    std::string endpoint;

    bool operator==(const AWSCloudCredential& rhs) const {
        return use_aws_sdk_default_behavior == rhs.use_aws_sdk_default_behavior &&
               use_instance_profile == rhs.use_instance_profile && access_key == rhs.access_key &&
               secret_key == rhs.secret_key && session_token == rhs.session_token && iam_role_arn == rhs.iam_role_arn &&
               sts_region == rhs.sts_region && sts_endpoint == rhs.sts_endpoint && external_id == rhs.external_id &&
               region == rhs.region && endpoint == rhs.endpoint;
    }
};

class AliyunCloudCredential final : public CloudCredential {
public:
    std::string access_key;
    std::string secret_key;
    std::string endpoint;

    bool operator==(const AliyunCloudCredential& rhs) const {
        return access_key == rhs.access_key && secret_key == rhs.secret_key && endpoint == rhs.endpoint;
    }
};

// Currently only supported for Azure Blob Storage
class AzureCloudCredential final : public CloudCredential {
public:
    std::string shared_key;
    std::string sas_token;
    std::string client_id;
    std::string client_secret;
    std::string tenant_id;

    bool operator==(const AzureCloudCredential& rhs) const {
        return shared_key == rhs.shared_key && sas_token == rhs.sas_token && client_id == rhs.client_id &&
               client_secret == rhs.client_secret && tenant_id == rhs.tenant_id;
    }
};

class CloudConfiguration {
public:
    virtual ~CloudConfiguration() = default;
};

class AWSCloudConfiguration final : public CloudConfiguration {
public:
    bool operator==(const AWSCloudConfiguration& rhs) const {
        return enable_path_style_access == rhs.enable_path_style_access && enable_ssl == rhs.enable_ssl &&
               aws_cloud_credential == rhs.aws_cloud_credential;
    }
    AWSCloudCredential aws_cloud_credential;
    bool enable_path_style_access = false;
    bool enable_ssl = true;
};

class AliyunCloudConfiguration final : public CloudConfiguration {
public:
    bool operator==(const AliyunCloudConfiguration& rhs) const {
        return aliyun_cloud_credential == rhs.aliyun_cloud_credential;
    }
    AliyunCloudCredential aliyun_cloud_credential;
};

class AzureCloudConfiguration final : public CloudConfiguration {
public:
    bool operator==(const AzureCloudConfiguration& rhs) const {
        return azure_cloud_credential == rhs.azure_cloud_credential;
    }

    AzureCloudCredential azure_cloud_credential;
};

} // namespace starrocks