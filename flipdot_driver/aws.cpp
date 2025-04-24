#include "aws.h"


#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

#include "hosts.h"
#include "cert.h"
BearSSL::X509List cert(cert_Amazon_RSA_2048_M03);
BearSSL::Session session;

bool getTime(JsonDocument &doc) {
  BearSSL::WiFiClientSecure client;
  client.setSession(&session);
  client.setTrustAnchors(&cert);

  HTTPClient https;

  Serial.print("[HTTPS] begin...\n");
  if (https.begin(client, lambda_host, lambda_port)) {  // HTTPS

    Serial.print("[HTTPS] GET...\n");
    // start connection and send HTTP header
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode <= 0) {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      return false;
    }
    Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

    if (httpCode != HTTP_CODE_OK) {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      return false;
    }

    String payload = https.getString();
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return false;
    }
    Serial.println(payload);

    https.end();
    return true;

  }
return false;
}