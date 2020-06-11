from pydrake.lcm import (
    DrakeLcm,
    DrakeLcmInterface, Subscriber
)
import drake.lcmt_polynomial
import drake.lcmt_contact_results_for_viz
import drake.lcmt_force_torque

mat = drake.lcmt_polynomial_matrix()
mat.polynomials.append(drake.lcmt_polynomial())
mat.encode()

mat = drake.lcmt_force_torque()
mat.timestamp = 32
mat.encode()

mat = drake.lcmt_contact_results_for_viz()
mat.timestamp = 32
