/*
 * IPFS.h
 *
 *  Created on: Oct 20, 2016
 *      Author: JohnJones
 */
#pragma once
#include <string>
#include <sstream>
#include "curl_easy.h"
#include "rapidjson/Document.h"

namespace ipfs_curl {

class IPFS {
public:
	IPFS();
	IPFS(std::string ip, int port, int apiPort)
		: gatewayIP(ip), gatewayPort(port), gatewayApiPort(apiPort) {}
	virtual ~IPFS();
public:
	std::ostringstream cat(std::string hash) {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayPort << "/ipfs/" << hash;
		return curl(url.str());
	}
	std::string add(std::string content) {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayApiPort << "/api/v0/add?stream-channels=true";
		rapidjson::Document json = curl_json(url.str(), content);
		return json["Hash"].GetString();
	}
	std::string ls(std::string hash) {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayApiPort << "/api/v0/ls/" << hash;
		rapidjson::Document json = curl_json(url.str());
		return json["Objects"][0]["Links"].GetString();
	}
	std::string size(std::string hash) {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayApiPort << "/api/v0/object/stat/" << hash;
		rapidjson::Document json = curl_json(url.str());
		return json["CumulativeSize"].GetString();
	}
	std::string pinAdd(std::string hash) {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayApiPort << "/api/v0/pin/add" << hash;
		rapidjson::Document json = curl_json(url.str());
		return json.GetString();
	}
	std::string version() {
		std::stringstream url;
		url << "http://" << gatewayIP << ":" << gatewayApiPort << "/api/v0/version";
		rapidjson::Document json = curl_json(url.str());
		return json["Version"].GetString();
	}
private:
	std::string gatewayIP;
	int gatewayPort;
	int gatewayApiPort;
private:
	rapidjson::Document curl_json(std::string url, std::string data = "") {
		std::string curlResult = curl(url, data).str();
		rapidjson::Document json;
		json.Parse(curlResult.c_str());
		return json;
	}
	std::ostringstream curl(std::string url, std::string data = "") {
		std::ostringstream output;
		curl::curl_ios<std::ostringstream> writer(output);

		curl::curl_easy easy(writer);

		easy.add<CURLOPT_URL>(url.c_str());
		//easy.add<CURLOPT_RETURNTRANSFER>(1L);
		easy.add<CURLOPT_TIMEOUT>(5);
		easy.add<CURLOPT_HEADER>(0);
		//easy.add<CURLOPT_BINARYTRANSFER>(1);
		try {
			easy.perform();
		} catch (curl::curl_easy_exception& error) {
			curl::curlcpp_traceback errors = error.get_traceback();
			error.print_traceback();
		}
		return output;
	}
};

} /* namespace ipfs_curl */
