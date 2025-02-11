//
// MIT License
//
// Copyright (c) 2020 Ross Newman (ross@rossnewman.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#define CATCH_CONFIG_MAIN
#include <unistd.h>

#include <catch/catch.hpp>
#include <iostream>

#include "events_gva.h"
#include "gva.h"
#include "hmi_gva.h"

using namespace gva;

static EventsGva *events = 0;

TEST_CASE("eventsGva Constructor1", "Constructor test") {
  events = new EventsGva(hmi::GetRendrer()->GetWindow(), hmi::GetRendrer()->GetTouch());

  REQUIRE(events != 0);
}

TEST_CASE("eventsGva", "flush") {
  //  events->flush();

  REQUIRE(events != 0);
  free(events);
}

TEST_CASE("eventsGva Constructor2", "Constructor test2") {
  // instantiate events
  EventKeyPowerOn on;

  hmi::start();
  hmi::dispatch(on);

  EventsGva io(hmi::GetRendrer()->GetWindow(), hmi::GetRendrer()->GetTouch());

  REQUIRE(hmi::GetRendrer()->GetWindow() != 0);
  REQUIRE(events != 0);
}
