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

#ifndef MULTICAST_WIFI_MODE
#define MULTICAST_WIFI_MODE

#include "ns3/object.h"
#include "ns3/string.h"
#include "ns3/mac48-address.h"
#include "ns3/ipv4.h"

namespace ns3
{

class MulticastGroup : public Object
{
    public:
        static TypeId GetTypeId(void);
        /**
        * Set de group address that identifies the group
        *
        * \param the group address
        */
        void SetGroupAddress(Mac48Address groupAddress);
        /**
        * Returns the mac address that identifies the group
        *
        * \return group's Mac48Address 
        */
        Mac48Address GetGroupAddress(void);
        /**
        * Sets the whole group to a pre-created group
        *
        * \param a vector with all group's mac addresses
        */
        void SetGroup(std::vector<Mac48Address>* group);
        /**
        * Returns a vector with all the addresses of the stations subscribed to the group
        *
        * \return a vector with all group's mac addresses
        */
        std::vector<Mac48Address>* GetGroup(void);
        /**
        * Adds a group member
        *
        * \param the Mac48Address of the member to be added
        */
        void AddGroupMember(Mac48Address member);
        /**
        * Deletes a group member
        *
        * \param the Mac48Address of the member to be deleted
        */
        void DeleteGroupMember(Mac48Address member);

    private:
        Mac48Address m_groupAddress;        //!< Group address
        std::vector<Mac48Address>* m_group;  //!< List of embers of the multicast group
};

class MulticastMode : public Object
{
    public:
        enum ModesList : int16_t
        {
            Legacy = 0, DMS = 1, GCRUR = 2, GCRIBACK = 3, GCRDBACK = 4
        };
        static TypeId GetTypeId(void);

        /**
        * Set the multicast transmission mode from the list
        *
        * \param mode integer from 0 to 4 that represents one of the modes in ModeList
        */
        void SetMode(int16_t mode);
        /**
        * Get the multicast transmission mode from the ones available in ModeList
        *
        * \return an integer corresponding to one of the modes in ModeList
        */
        int16_t GetMode(void) const;
        /**
        * Set the number of retries used in GCR-UR 
        *
        * \param retries integer representing the number of retries
        */
        void SetRetries(int16_t retries);
        /**
        * Get the number of retries used in GCR-UR
        *
        * \return an integer indicating the number of retries
        */
        int16_t GetRetries(void) const;
        /**
        * Set the order of the retry (if there are 3 retries, it indicates if this one was the
        * first, the second or the third)
        *
        * \param retry  integer representing the order of this retry
        */
        void SetRetry(int16_t retry);
        /**
        * Returns an integer indicating the order of the retry (if there are 3 retries,
        * it indicates if this was the first the second or the third).
        *
        * \return an integer indicating the order of this retry
        */
        int16_t GetRetry(void) const;
        /**
        * Set an array of multicast groups that are managed by the AP.
        *
        * \param groups an pointer to a vector of multicast groups
        */
        void SetGroups(std::vector<MulticastGroup>* groups);
        /**
        * Returns all the groups being managed by this object.
        *
        * \return a pointer to a vector containing the mac addresses of all the members of the group
        */
        std::vector<MulticastGroup>*  GetGroups(void) const;
        /**
        * Register a new client in a group
        *
        * \param group the group mac address
        * \param client the mac address of the client to be registered
        */
        void Register(Mac48Address group, Mac48Address client);
        /**
        * Delete a new client from a group
        *
        * \param group the group mac address
        * \param client the mac address of the client to be delited
        */
        void DeRegister(Mac48Address group, Mac48Address client);
        /**
        * Returns all the clients in a group
        *
        * \param group the group mac address
        * \return a pointer to a vector containing the mac addresses of all the members of the group
        */
        std::vector<Mac48Address>* GetGroup(Mac48Address group);

    private:
        int16_t m_multicastmode;              //!< Defines the multicast transmission mode from the ones available at IEEE 802.11aa
        int16_t m_retries;                    //!< The number of retries for those modes that support the
        int16_t m_retry;                      //!< A number identifying the retry from 0 to Retries
        std::vector<MulticastGroup>* m_groups; //!< vector with the MulticastGroup object containing subscriptions
};

}

#endif