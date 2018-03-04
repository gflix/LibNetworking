#ifndef NETWORKING_TCP_GENERICTCP_H_
#define NETWORKING_TCP_GENERICTCP_H_

#define TCP_INVALID_DESCRIPTOR (-1)
#define TCP_PORT_MIN (1)
#define TCP_PORT_MAX (65535)

namespace Flix {

class GenericTcp {
public:
    GenericTcp();
    virtual ~GenericTcp();

    bool isConnected(void) const;
    int getDescriptor(void) const;

protected:
    int descriptor;

    bool withinRange(int value, int min, int max) const;
};

} /* namespace Flix */

#endif /* NETWORKING_TCP_GENERICTCP_H_ */
