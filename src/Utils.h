#pragma once

#include <string>
#include "Models.h"
#include "rapidjson/document.h"

class Utils {
public:
    static bool ParseJsonResponse(const std::string& response, rapidjson::Document& document);
    static std::string Base64Decode(const std::string& base64Data);
    static std::string UrlEncode(const std::string& value);
    static bool ParseDrmJsonToConfig(const rapidjson::Value& drmJson, DRMConfig& config);
    static time_t ParseISO8601(const std::string& isoString);
    static std::string ToISO8601(time_t time);
    static int GenerateProviderUniqueId(const std::string& providerName);
    // Kodi identifies channels by a unique id that must not collide; several
    // providers reuse one display number for multiple stations (e.g. an SD and
    // an HD variant), so the id is derived from provider and channel id.
    static int GenerateChannelUniqueId(const std::string& provider, const std::string& channelId);

private:
    static int Djb2Hash(const std::string& value);
};