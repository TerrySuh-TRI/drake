from pydrake.lcm import (
    DrakeLcm,
    DrakeLcmInterface, Subscriber
)

import drake
import time

class LCMSubscriber():
    
    def __init__(self):
        self.lcm = DrakeLcm()
        self.lcm_type = drake.lcmt_contact_results_for_viz()
        self.clear()
        self.lcm.Subscribe(channel ="CONTACT_RESULTS", handler=self._handler)

    def clear(self):
        self.count = 0
        self.raw = []
        self.message = self.lcm_type

    def _handler(self, msg):
        self.count += 1
        self.raw = msg 
        self.message = self.lcm_type.decode(msg)

        print(self.message.point_pair_contact_info[2].body1_name)
        print(self.message.point_pair_contact_info[2].body2_name)
        print(self.message.point_pair_contact_info[2].normal)

if __name__ == '__main__':
    L = LCMSubscriber()
    while(L.lcm.HandleSubscriptions(1000)):
        pass




