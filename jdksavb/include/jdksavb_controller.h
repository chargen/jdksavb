#pragma once

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
#include "jdksavb_entity.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup controller  */
/*@{*/

/// jdksavb_controller inherits jdksavb_entity and is the base class for an Controller entity
struct jdksavb_controller {
    struct jdksavb_entity base;

    bool (*received_aa_response)(struct jdksavb_entity *self,
                                 struct jdksavdecc_aecp_aa const *aa,
                                 jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                 uint8_t *buf,
                                 uint16_t len);

    bool (*received_aem_response)(struct jdksavb_entity *self,
                                  struct jdksavdecc_aecpdu_aem const *aem,
                                  jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                  uint8_t *buf,
                                  uint16_t len);

    /// Formulate and send a ACQUIRE_ENTITY command to a target entity
    void (*send_acquire_entity)(struct jdksavb_entity *self,
                                struct jdksavdecc_eui64 const *target_entity_id,
                                struct jdksavdecc_eui48 const *target_mac_address,
                                uint32_t flags);

    bool (*receive_acquire_entity_response)(struct jdksavb_entity *self,
                                            struct jdksavdecc_aecpdu_aem const *aem,
                                            jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                            uint8_t *buf,
                                            uint16_t len);

    /// Formulate and send a LOCK_ENTITY command to a target entity
    void (*send_lock_entity)(struct jdksavb_entity *self,
                             struct jdksavdecc_eui64 const *target_entity_id,
                             struct jdksavdecc_eui48 const *target_mac_address,
                             uint32_t flags);

    bool (*receive_lock_entity_response)(struct jdksavb_entity *self,
                                         struct jdksavdecc_aecpdu_aem const *aem,
                                         jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                         uint8_t *buf,
                                         uint16_t len);

    // Formulate and send a READ_DESCRIPTOR command to a target entity
    void (*send_read_descriptor)(struct jdksavdecc_eui64 const *target_entity_id,
                                 struct jdksavdecc_eui48 const *target_mac_address,
                                 uint16_t configuration_index,
                                 uint16_t descriptor_type,
                                 uint16_t descriptor_index);

    bool (*receive_read_descriptor_response)(struct jdksavb_entity *self,
                                             struct jdksavdecc_aecpdu_aem const *aem,
                                             jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                             uint8_t *buf,
                                             uint16_t len);

    // Formulate and send a SET_CONFIGURATION command to a target entity
    void (*send_set_configuration)(struct jdksavdecc_eui64 const *target_entity_id,
                                   struct jdksavdecc_eui48 const *target_mac_address,
                                   uint16_t configuration_index);

    bool (*receive_set_configuration_response)(struct jdksavb_entity *self,
                                               struct jdksavdecc_aecpdu_aem const *aem,
                                               jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                               uint8_t *buf,
                                               uint16_t len);

    // Formulate and send a SET_NAME command to a target entity
    void (*send_set_name)(struct jdksavdecc_eui64 const *target_entity_id,
                          struct jdksavdecc_eui48 const *target_mac_address,
                          uint16_t target_descriptor_type,
                          uint16_t target_descriptor_index,
                          uint16_t name_index,
                          uint16_t configuration_index,
                          struct jdksavdecc_string const *name);

    bool (*receive_set_name_response)(struct jdksavb_entity *self,
                                      struct jdksavdecc_aecpdu_aem const *aem,
                                      jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                      uint8_t *buf,
                                      uint16_t len);

    // Formulate and send a GET_NAME command to a target entity
    void (*send_get_name)(struct jdksavdecc_eui64 const *target_entity_id,
                          struct jdksavdecc_eui48 const *target_mac_address,
                          uint16_t target_descriptor_type,
                          uint16_t target_descriptor_index,
                          uint16_t name_index,
                          uint16_t configuration_index,
                          struct jdksavdecc_string const *name);

    bool (*receive_get_name_response)(struct jdksavb_entity *self,
                                      struct jdksavdecc_aecpdu_aem const *aem,
                                      jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                      uint8_t *buf,
                                      uint16_t len);

    // Formulate and send a SET_CONTROL command to a target entity
    void (*send_set_control)(struct jdksavdecc_eui64 const *target_entity_id,
                             struct jdksavdecc_eui48 const *target_mac_address,
                             uint16_t target_descriptor_index,
                             uint8_t *control_value,
                             uint16_t control_value_len,
                             bool track_for_ack);

    bool (*receive_set_control_response)(struct jdksavb_entity *self,
                                         struct jdksavdecc_aecpdu_aem const *aem,
                                         jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                         uint8_t *buf,
                                         uint16_t len);

    // Formulate and send a REGISTER_UNSOLICITED_NOTIFICATION command to a target entity
    void (*send_register_unsolicited_notification)(struct jdksavdecc_eui64 const *target_entity_id,
                                                   struct jdksavdecc_eui48 const *target_mac_address);

    bool (*receive_register_unsolicited_notification_response)(struct jdksavb_entity *self,
                                                               struct jdksavdecc_aecpdu_aem const *aem,
                                                               jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                                               uint8_t *buf,
                                                               uint16_t len);

    // Formulate and send a DEREGISTER_UNSOLICITED_NOTIFICATION command to a target entity
    void (*send_deregister_unsolicited_notification)(struct jdksavdecc_eui64 const *target_entity_id,
                                                     struct jdksavdecc_eui48 const *target_mac_address);

    bool (*receive_deregister_unsolicited_notification_response)(struct jdksavb_entity *self,
                                                                 struct jdksavdecc_aecpdu_aem const *aem,
                                                                 jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                                                 uint8_t *buf,
                                                                 uint16_t len);

    // Formulate and send a GET_CONTROL command to a target entity
    void (*send_get_control)(struct jdksavdecc_eui64 const *target_entity_id,
                             struct jdksavdecc_eui48 const *target_mac_address,
                             uint16_t target_descriptor_index);

    bool (*receive_get_control_response)(struct jdksavb_entity *self,
                                         struct jdksavdecc_aecpdu_aem const *aem,
                                         jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                         uint8_t *buf,
                                         uint16_t len);
};

/// Initialize an jdksavdecc_adp with the specified context and frame_send function and
/// received_entity_available_or_departing function
bool jdksavb_controller_init(struct jdksavb_controller *self,
                             struct jdksavdecc_entity_model *entity_model,
                             int symbol_dispatch_table_num_entries,
                             struct jdksavb_symbol_dispatch *symbol_dispatch_table,
                             void *context,
                             void (*frame_send)(struct jdksavb_entity *self, void *context, uint8_t const *buf, uint16_t len));

/// Destroy any resources that the jdksavdecc_adp uses
void jdksavb_controller_destroy(struct jdksavb_entity *self);

bool jdksavb_controller_received_aa_response(struct jdksavb_entity *self,
                                             struct jdksavdecc_aecp_aa const *aa,
                                             jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                             uint8_t *buf,
                                             uint16_t len);

bool jdksavb_controller_received_aem_response(struct jdksavb_entity *self,
                                              struct jdksavdecc_aecpdu_aem const *aem,
                                              jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                              uint8_t *buf,
                                              uint16_t len);

void jdksavb_controller_send_acquire_entity(struct jdksavb_entity *self,
                                            struct jdksavdecc_eui64 const *target_entity_id,
                                            struct jdksavdecc_eui48 const *target_mac_address,
                                            uint32_t flags);

bool jdkavdecc_controller_receive_acquire_entity_response(struct jdksavb_entity *self,
                                                          struct jdksavdecc_aecpdu_aem const *aem,
                                                          jdksavdecc_timestamp_in_milliseconds cur_time_in_ms,
                                                          uint8_t *buf,
                                                          uint16_t len);

bool jdksavb_controller_receive(struct jdksavb_entity *self,
                                void *context,
                                jdksavdecc_timestamp_in_milliseconds time_in_milliseconds,
                                uint8_t *buf,
                                uint16_t len);

void jdksavb_controller_received_entity_available_or_departing(struct jdksavb_entity *self,
                                                               void *context,
                                                               void const *source_address,
                                                               int source_address_len,
                                                               struct jdksavdecc_adpdu *adpdu);

/*@}*/

#ifdef __cplusplus
}
#endif
