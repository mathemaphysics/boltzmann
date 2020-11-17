=========
Boltzmann
=========

Introduction
============

This is the beginning of a Boltzmann machine simulator. A number of sets of
software already exist to implement deep learning systems involving
feedforward networks for e.g. classification. Many of these are capable of
simulating restricted Boltzmann machines but are not built explicitly for
such use, particularly in the mode of operation typically associated with
Boltzmann machines, asynchronous stochastic update via the flipping
probability. So this implementation will focus specifically on these details.

In general, Boltzmann machines are systems of nodes which behave very much
like neurons which are interconnected and interact with one another via a
stochastic rule. For example whether or not node 1 is activated depends on
the states of nodes 2, 3 and 4 which are connected to it. The total signal
coming from 2, 3, and 4 is calculated and put into a function which returns a
value between 0.0 and 1.0. A random number is then "rolled". If this number
is less than the calculated function value, the neuron is switched on,
otherwise it remains off (assuming it was originally off). A similar
procedure applies to the case in which the neuron is initially on. Those
familiar with the Metropolis-Hastings algorithm will recognize this as
identical to the Monte Carlo method commonly used in simulating very large
molecular systems and even quantum mechanical systems (via quantum Monte
Carlo, QMC).

.. math::

   $$ a_i = \sum_{n ~ u} u(a(n)) $$