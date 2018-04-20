#!/usr/bin/python
# -*- coding: utf-8 -*-
from suds.client import Client

c = Client('http://localhost:8000/?wsdl')
c.service.say_hello('dafaasd', '5.34,23.23')

