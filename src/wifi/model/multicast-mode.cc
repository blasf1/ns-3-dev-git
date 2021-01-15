/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2021 Blas Gomez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Blas Gómez <blas.gomez@uclm.es>
 */

#include "multicast-mode.h"
#include "ns3/integer.h"
#include "ns3/pointer.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE ("MulticastMode");

TypeId 
MulticastGroup::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::MulticastMode")
        .SetParent<Object>()
        .SetGroupName("Wifi")
        ;
    return tid;
}

void
MulticastGroup::SetGroupAddress(Mac48Address groupAddress)
{
    m_groupAddress = groupAddress;
}

Mac48Address
MulticastGroup::GetGroupAddress(void)
{
    return m_groupAddress;
}

void
MulticastGroup::SetGroup(std::vector<Mac48Address>* group)
{
    m_group = group;
}

std::vector<Mac48Address>*
MulticastGroup::GetGroup(void)
{
    return m_group;
}

void
MulticastGroup::AddGroupMember(Mac48Address member)
{
    if(m_group == nullptr)
    {
        m_group = new std::vector<Mac48Address>();
    }
    m_group->push_back(member);
}

void
MulticastGroup::DeleteGroupMember(Mac48Address member)
{
    for(auto i = m_group->begin() ; i != m_group->end(); i++)
    {
        if(*i == member)
        {
            m_group->erase(i);
            break;
        }
    }
}

TypeId 
MulticastMode::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::MulticastMode")
        .SetParent<Object>()
        .SetGroupName("Wifi")
        .AddAttribute("Mode", "The available multicast modes"
                      "choose the multicast mode",
                      IntegerValue(0),
                      MakeIntegerAccessor(&MulticastMode::SetMode,
                                          &MulticastMode::GetMode),
                      MakeIntegerChecker<int16_t>())
        .AddAttribute("Retries", "The number of retries for those modes that support them"
                      "Default is 3",
                      IntegerValue(3),
                      MakeIntegerAccessor(&MulticastMode::SetRetries,
                                          &MulticastMode::GetRetries),
                      MakeIntegerChecker<int16_t>())
        .AddAttribute("Retry", "A number identifying the retry from 0 to Retries",
                      IntegerValue(0),
                      MakeIntegerAccessor(&MulticastMode::SetRetry,
                                          &MulticastMode::GetRetry),
                      MakeIntegerChecker<int16_t>())
        ; 
    return tid;
}

void
MulticastMode::SetMode(int16_t mode)
{
    m_multicastmode = mode;
}

int16_t 
MulticastMode::GetMode(void) const
{
    return m_multicastmode;
}

void
MulticastMode::SetRetries(int16_t retries)
{
    m_retries = retries;
}

int16_t 
MulticastMode::GetRetries(void) const
{
    return m_retries;
}

void
MulticastMode::SetRetry(int16_t retry)
{
    m_retry = retry;
}

int16_t
MulticastMode::GetRetry(void) const
{
    return m_retry;
}

void
MulticastMode::SetGroups(std::vector<MulticastGroup>* groups)
{
    m_groups = groups;
}

std::vector<MulticastGroup>* 
MulticastMode::GetGroups(void) const
{
    return m_groups;
}

void
MulticastMode::Register(Mac48Address group, Mac48Address client)
{
    if(m_groups == nullptr)
    {
        m_groups = new std::vector<MulticastGroup>();
        MulticastGroup newGroup;
        newGroup.SetGroupAddress(group);
        m_groups->push_back(newGroup);
    }
    for(auto i = m_groups->begin(); i != m_groups->end(); i++)
    {
        if(i->GetGroupAddress() == group)
        {
            i->AddGroupMember(client);
        }
    }
}

void
MulticastMode::DeRegister(Mac48Address group, Mac48Address client)
{
    for(MulticastGroup element : *m_groups)
    {
        if(element.GetGroupAddress() == group)
        {
            element.DeleteGroupMember(client);
            if(element.GetGroup()->empty())
            {
                for(auto i = m_groups->begin() ; i != m_groups->end(); i++)
                {
                    m_groups->erase(i);
                    break;
                }
            }
        }
    }
}

std::vector<Mac48Address>*
MulticastMode::GetGroup(Mac48Address group)
{
    std::vector<Mac48Address>* stations = new std::vector<Mac48Address>();

    for(MulticastGroup element : *m_groups)
    {
        if(element.GetGroupAddress() == group)
        {
            return element.GetGroup();
            break;
        }
    }
    return stations;
}

}