// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file locationSubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>

#include "locationSubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

locationSubscriber::locationSubscriber() : mp_participant(nullptr), mp_subscriber(nullptr) {}

locationSubscriber::~locationSubscriber() {	Domain::removeParticipant(mp_participant);}

bool locationSubscriber::init()
{
    // Create RTPSParticipant

    ParticipantAttributes PParam;
    PParam.rtps.builtin.domainId = 0; //MUST BE THE SAME AS IN THE PUBLISHER
    PParam.rtps.builtin.leaseDuration = c_TimeInfinite;
    PParam.rtps.setName("Participant_subscriber"); //You can put the name you want
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant == nullptr)
    {
        return false;
    }

    //Register the type

    Domain::registerType(mp_participant, static_cast<TopicDataType*>(&myType));

    // Create Subscriber

    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = myType.getName(); //Must be registered before the creation of the subscriber
    Rparam.topic.topicName = "locationPubSubTopic";
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    return true;
}

void locationSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
{
    (void)sub;

    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched" << std::endl;
    }
}

void locationSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{

    if(sub->takeNextData(&m_geo, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            // Print your structure data here.
            ++n_msg;
            std::cout << "Azimuth received, count=" << n_msg << std::endl;
        }
    }
}

void locationSubscriber::getUpdate(uint16_t *cameraAzimuth)
{
  *cameraAzimuth = m_geo.cameraAzimuth();
}
