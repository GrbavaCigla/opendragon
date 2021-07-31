| Report Data Fragment             | Function                                                                     |
| -------------------------------- | ---------------------------------------------------------------------------- |
| 02f10202000000000000000000000000 | Fully lit blue for 5s (possibly because of USB_CTRL_SET_TIMEOUT which is 5s) |
| 020300307d6277000000000100000000 | Same as above                                                                |
| 02f10204000000000000000000000000 | Wave mode                                                                    |

A lot of different reports cause mouse to go blue (maybe some programming mode or something).
Since this is captured from profile change, maybe wave mode is actually changing to another profile.
