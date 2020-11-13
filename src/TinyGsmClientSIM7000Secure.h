#ifndef SRC_TINYGSMCLIENTSIM7000SECURE_H_
#define SRC_TINYGSMCLIENTSIM7000SECURE_H_

#define TINY_GSM_MUX_COUNT 2

#include "TinyGsmClientSIM7000.h"
#include "TinyGsmSSL.tpp"

class TinyGsmSim7000Secure : public TinyGsmSim7000, public TinyGsmSSL<TinyGsmSim7000Secure> {
  friend class TinyGsmSSL<TinyGsmSim7000Secure>;

  public:
    explicit TinyGsmSim7000Secure(Stream& stream) : TinyGsmSim7000(stream) {};

    class GsmClientSecureSim7000 : public GsmClientSim7000 {
      friend class TinyGsmSim7000Secure;

      public:
        GsmClientSecureSim7000() {};

        GsmClientSecureSim7000(TinyGsmSim7000Secure& modem, uint8_t mux = 0) : GsmClientSim7000(modem, mux) {};
    };

  protected:
    bool gprsConnectImpl(const char* apn, const char* user = NULL, const char* pwd = NULL) override {
      gprsDisconnect();

      sendAT(GF("+CNACT=1,\""), apn, "\"");
      if (waitResponse(60000L) != 1) { return false; }

      return true;
    }

    bool gprsDisconnectImpl() override {
      sendAT(GF("+CNACT=0"));
      if (waitResponse(60000L) != 1) { return false; }

      return true;
    }

    String getLocalIPImpl() override {
      sendAT(GF("+CNACT?"));

      if (waitResponse(GF("+CNACT:")) != 1) { return ""; }

      // Get the IP which is enclosed in '"'
      String res;
      res = stream.readStringUntil('\"');
      res = stream.readStringUntil('\"');

      return res;
    }

    GsmClientSecureSim7000* sockets[TINY_GSM_MUX_COUNT];
};

#endif  // SRC_TINYGSMCLIENTSIM7000SECURE_H_
