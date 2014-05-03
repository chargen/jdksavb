/*
Copyright (c) 2014, Jeff Koftinoff
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the {organization} nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "jdksavb_world.h"
#include "jdksavb_acmp_talker.h"


void jdksavb_acmp_talker_stream_source_init(
        struct jdksavb_acmp_talker_stream_source *self,
        void *context,
        uint16_t talker_unique_id) {
    self->context = context;
    self->talker_unique_id = talker_unique_id;
    jdksavdecc_eui48_init(&self->destination_mac_address);
    jdksavdecc_eui64_init(&self->stream_id);
    self->flags = 0;
    self->stream_vlan_id = 0;
    jdksavb_acmp_talker_stream_source_clear_listeners(self);
}

void jdksavb_acmp_talker_stream_source_update(
        struct jdksavb_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 new_stream_id,
        struct jdksavdecc_eui48 new_destination_mac_address,
        uint16_t new_stream_vlan_id ) {
    self->stream_id = new_stream_id;
    self->destination_mac_address = new_destination_mac_address;
    self->stream_vlan_id = new_stream_vlan_id;
}

void jdksavb_acmp_talker_stream_source_clear_listeners(
        struct jdksavb_acmp_talker_stream_source *self) {
    int i;

    self->connection_count = 0;
    for( i=0; i<JDKSAVB_ACMP_TALKER_MAX_LISTENERS_PER_STREAM; ++i ) {
        jdksavdecc_eui64_init(&self->listener_entity_id[i]);
        self->listener_unique_id[i]=0;
    }
}

bool jdksavb_acmp_talker_stream_source_add_listener(
        struct jdksavb_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 listener_entity_id,
        uint16_t listener_unique_id
        ) {
    bool r=false;
    int item = self->connection_count;
    if( item < JDKSAVB_ACMP_TALKER_MAX_LISTENERS_PER_STREAM ) {
        self->connection_count++;
        self->listener_entity_id[item] = listener_entity_id;
        self->listener_unique_id[item] = listener_unique_id;
        r=true;
    }
    return r;
}

bool jdksavb_acmp_talker_stream_source_remove_listener(
        struct jdksavb_acmp_talker_stream_source *self,
        struct jdksavdecc_eui64 listener_entity_id,
        uint16_t listener_unique_id
        ) {
    bool r=false;
    int i;
    for( i=0; i<self->connection_count; ++i ) {
        if( self->listener_unique_id[i] == listener_unique_id &&
            jdksavdecc_eui64_compare(&self->listener_entity_id[i], &listener_entity_id)==0) {
            /* Found it. Replace it with the last one in the list if there is one and it isn't this one */
            if( self->connection_count>0 ) {
                int last_item = self->connection_count-1;
                if( last_item!=i ) {
                    self->listener_entity_id[i] = self->listener_entity_id[last_item];
                    self->listener_unique_id[i] = self->listener_unique_id[last_item];
                    /* and erase the old last item so debugging is nicer */
                    jdksavdecc_eui64_init(&self->listener_entity_id[last_item]);
                    self->listener_unique_id[i] = 0;
                }
            }

            r=true;
            break;
        }
    }
    return r;
}

