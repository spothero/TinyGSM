#ifndef SRC_TINYGSMCLIENTSIM7000SECURE_H_
#define SRC_TINYGSMCLIENTSIM7000SECURE_H_

#include "TinyGsmClientSIM7000.h"
#include "TinyGsmSSL.tpp"

class TinyGsmSim7000Secure : public TinyGsmSim7000, public TinyGsmSSL<TinyGsmSim7000Secure> {
  friend class TinyGsmSSL<TinyGsmSim7000Secure>;

  public:
    explicit TinyGsmSim7000Secure(Stream& stream) : TinyGsmSim7000(stream) {}

    class GsmClientSecureSim7000 : public GsmClientSim7000 {
      public:
        GsmClientSecureSim7000() {}

        GsmClientSecureSim7000(TinyGsmSim7000Secure& modem, uint8_t mux = 0) : GsmClientSim7000(modem, mux) {}
    };
};

#endif  // SRC_TINYGSMCLIENTSIM7000SECURE_H_
