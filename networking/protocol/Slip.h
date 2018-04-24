#ifndef NETWORKING_PROTOCOL_SLIP_H_
#define NETWORKING_PROTOCOL_SLIP_H_

#include <string>
#include <vector>

namespace Flix {

typedef std::string SlipFrame;
typedef std::vector<SlipFrame> SlipFrames;

class Slip {
public:
    Slip();
    virtual ~Slip();

    void appendReceivedData(const std::string& receivedData);
    void resetReceiveBuffer(void);
    const std::string getReceiveBuffer(void) const;
    void getFrameDelimiters(std::string::size_type& first, std::string::size_type& second) const;

    bool hasFrame(void) const;
    void getFrame(SlipFrame& frame);
    void getFrames(SlipFrames& frames);

    std::string escapeFrame(const SlipFrame& input) const;
    std::string unescapeFrame(const SlipFrame& input) const;

private:
    std::string receiveBuffer;
};

} /* namespace Flix */

#endif /* NETWORKING_PROTOCOL_SLIP_H_ */
