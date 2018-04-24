#ifndef NETWORKING_PROTOCOL_SLIP_H_
#define NETWORKING_PROTOCOL_SLIP_H_

#include <string>

namespace Flix {

class Slip {
public:
    Slip();
    virtual ~Slip();

    void appendReceivedData(const std::string& receivedData);
    void resetReceiveBuffer(void);
    const std::string getReceiveBuffer(void) const;
    void getFrameDelimiters(std::string::size_type& first, std::string::size_type& second) const;

    bool hasFrame(void) const;
    void getFrame(std::string& frame);

private:
    std::string receiveBuffer;
};

} /* namespace Flix */

#endif /* NETWORKING_PROTOCOL_SLIP_H_ */
