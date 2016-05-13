/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file
/// \brief All the message identifiers used by RakNet.  Message identifiers comprise the first byte of any message.
///


#ifndef __MESSAGE_IDENTIFIERS_H
#define __MESSAGE_IDENTIFIERS_H 

#if defined(RAKNET_USE_CUSTOM_PACKET_IDS)
#include "CustomPacketIdentifiers.h"
#else

enum OutOfBandIdentifiers
{
	ID_NAT_ESTABLISH_UNIDIRECTIONAL, //����͸
	ID_NAT_ESTABLISH_BIDIRECTIONAL, //˫��͸
	ID_NAT_TYPE_DETECT, //ƥ������
	ID_ROUTER_2_REPLY_TO_SENDER_PORT, //·������ʱ���Ͷ˿�
	ID_ROUTER_2_REPLY_TO_SPECIFIED_PORT, //�ض��˿�
	ID_ROUTER_2_MINI_PUNCH_REPLY, //�ظ�
	ID_ROUTER_2_MINI_PUNCH_REPLY_BOUNCE, //����
	ID_XBOX_360_VOICE, //����
	ID_XBOX_360_GET_NETWORK_ROOM, //��ȡ���緿��
	ID_XBOX_360_RETURN_NETWORK_ROOM, //�������緿��
	ID_NAT_PING, //ping����
	ID_NAT_PONG, //pong����
};

/// You should not edit the file MessageIdentifiers.h as it is a part of RakNet static library
/// To define your own message id, define an enum following the code example that follows. 
///  �Զ����¼�����
/// \code
/// enum {
///   ID_MYPROJECT_MSG_1 = ID_USER_PACKET_ENUM,
///   ID_MYPROJECT_MSG_2, 
///    ... 
/// };
/// \endcode 
///
/// \note All these enumerations should be casted to (unsigned char) before writing them to RakNet::BitStream
//��֮ǰ �����¼�
enum DefaultMessageIDTypes
{
	//
	// RESERVED TYPES - DO NOT CHANGE THESE
	// RakPeer �¼�����
	//
	/// ��Щ������Զ����Żظ��û�
	ID_CONNECTED_PING,  /// ping����ϵͳ������ʱ������ڲ�ʹ�ã� 

	ID_UNCONNECTED_PING, //ping �Ͽ�ϵͳ������Ӧ����������ʱ����� Ping from an unconnected system.  Reply but do not update timestamps. (internal use only)

	ID_UNCONNECTED_PING_OPEN_CONNECTIONS,//Pong �Ͽ�ϵͳ������Ӧ����������ʱ�����Ping from an unconnected system.  Only reply if we have open connections. Do not update timestamps. (internal use only)

	ID_CONNECTED_PONG,// Pong����ϵͳ������ʱ������ڲ�ʹ�ã��� Pong from a connected system.  Update timestamps (internal use only)

	ID_DETECT_LOST_CONNECTIONS, //һ���ɿ������ݰ���ⶪʧ�����ӣ������ڲ�ʹ�ã� A reliable packet to detect lost connections (internal use only)

	/// C2S: Initial query: Header(1), OfflineMesageID(16), Protocol number(1), Pad(toMTU), sent with no fragment set.
	/// If protocol fails on server, returns ID_INCOMPATIBLE_PROTOCOL_VERSION to client
	ID_OPEN_CONNECTION_REQUEST_1,//��һ������

	/// S2C: Header(1), OfflineMesageID(16), server GUID(8), HasSecurity(1), Cookie(4, if HasSecurity)
	/// , public key (if do security is true), MTU(2). If public key fails on client, returns ID_PUBLIC_KEY_MISMATCH
	ID_OPEN_CONNECTION_REPLY_1, //��һ�λظ� ͷ��Ϣ��������Ϣid��������id��ʶ����Կ��cookie����Կ��mtu �����Կʧ���򷵻� ID_PUBLIC_KEY_MISMATCH

	/// C2S: Header(1), OfflineMesageID(16), Cookie(4, if HasSecurity is true on the server), clientSupportsSecurity(1 bit),
	/// handshakeChallenge (if has security on both server and client), remoteBindingAddress(6), MTU(2), client GUID(8)
	/// Connection slot allocated if cookie is valid, server is not full, GUID and IP not already in use.
	ID_OPEN_CONNECTION_REQUEST_2, //�ڶ������� ͷ��Ϣ��������Ϣid��cookie���ͻ���֧����Կ������ͨ�������ӵ�ַ��mtu���ͻ���id��ʶ�����Ӳ�

	/// S2C: Header(1), OfflineMesageID(16), server GUID(8), mtu(2), doSecurity(1 bit), handshakeAnswer (if do security is true)
	ID_OPEN_CONNECTION_REPLY_2, //�ڶ��λظ� ͷ��Ϣ��������Ϣid��������id��ʶ��mtu��ִ����Կ�����ֻش������Կ�ɹ���

	/// C2S: Header(1), GUID(8), Timestamp, HasSecurity(1), Proof(32)
	ID_CONNECTION_REQUEST, //��������ͷ��Ϣ��id��ʶ��ʱ�������Կ����Կ

	/// RakPeer - Remote system requires secure connections, pass a public key to RakPeerInterface::Connect()
	ID_REMOTE_SYSTEM_REQUIRES_PUBLIC_KEY,//Զ��ϵͳҪ����Կ���ӣ�ͨ��������

	/// RakPeer - We passed a public key to RakPeerInterface::Connect(), but the other system did not have security turned on
	ID_OUR_SYSTEM_REQUIRES_SECURITY,//��������ϵͳδ��⹫Կ������ͨ����Կ���ӣ�

	/// RakPeer - Wrong public key passed to RakPeerInterface::Connect()
	ID_PUBLIC_KEY_MISMATCH,//��Կ����

	/// RakPeer - Same as ID_ADVERTISE_SYSTEM, but intended for internal use rather than being passed to the user.
	/// Second byte indicates type. Used currently for NAT punchthrough for receiver port advertisement. See ID_NAT_ADVERTISE_RECIPIENT_PORT
	ID_OUT_OF_BAND_INTERNAL, //�������أ��ڶ��ֽ�˵����

	/// If RakPeerInterface::Send() is called where PacketReliability contains _WITH_ACK_RECEIPT, then on a later call to
	/// RakPeerInterface::Receive() you will get ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS. The message will be 5 bytes long,
	/// and bytes 1-4 inclusive will contain a number in native order containing a number that identifies this message.
	/// This number will be returned by RakPeerInterface::Send() or RakPeerInterface::SendList(). ID_SND_RECEIPT_ACKED means that
	/// the message arrived
	ID_SND_RECEIPT_ACKED, //�ɿ�����Ϣ

	/// If RakPeerInterface::Send() is called where PacketReliability contains UNRELIABLE_WITH_ACK_RECEIPT, then on a later call to
	/// RakPeerInterface::Receive() you will get ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS. The message will be 5 bytes long,
	/// and bytes 1-4 inclusive will contain a number in native order containing a number that identifies this message. This number
	/// will be returned by RakPeerInterface::Send() or RakPeerInterface::SendList(). ID_SND_RECEIPT_LOSS means that an ack for the
	/// message did not arrive (it may or may not have been delivered, probably not). On disconnect or shutdown, you will not get
	/// ID_SND_RECEIPT_LOSS for unsent messages, you should consider those messages as all lost.
	ID_SND_RECEIPT_LOSS, //��ʧ
	

	//
	// USER TYPES - DO NOT CHANGE THESE
	// �û�ʹ�����ͣ���Ҫ�ı���Щ��

	/// RakPeer - In a client/server environment, our connection request to the server has been accepted.
	ID_CONNECTION_REQUEST_ACCEPTED,

	/// RakPeer - Sent to the player when a connection request cannot be completed due to inability to connect. 
	ID_CONNECTION_ATTEMPT_FAILED, //��������ʧ��

	/// RakPeer - Sent a connect request to a system we are currently connected to.
	ID_ALREADY_CONNECTED, //�Ѿ�����

	/// RakPeer - A remote system has successfully connected.
	ID_NEW_INCOMING_CONNECTION, //�µ���������

	/// RakPeer - The system we attempted to connect to is not accepting new connections.
	ID_NO_FREE_INCOMING_CONNECTIONS, //�Ѿ�����

	/// RakPeer - The system specified in Packet::systemAddress has disconnected from us.  For the client, this would mean the
	/// server has shutdown. 
	ID_DISCONNECTION_NOTIFICATION, //�Ͽ�����֪ͨ

	/// RakPeer - Reliable packets cannot be delivered to the system specified in Packet::systemAddress.  The connection to that
	/// system has been closed. 
	ID_CONNECTION_LOST, //���Ӷ�ʧ

	/// RakPeer - We are banned from the system we attempted to connect to.
	ID_CONNECTION_BANNED, //��ֹ����

	/// RakPeer - The remote system is using a password and has refused our connection because we did not set the correct password.
	ID_INVALID_PASSWORD, //��Ч����

	// RAKNET_PROTOCOL_VERSION in RakNetVersion.h does not match on the remote system what we have on our system
	// This means the two systems cannot communicate.
	// The 2nd byte of the message contains the value of RAKNET_PROTOCOL_VERSION for the remote system
	ID_INCOMPATIBLE_PROTOCOL_VERSION, //Э��汾

	// Means that this IP address connected recently, and can't connect again as a security measure. See
	/// RakPeer::SetLimitIPConnectionFrequency()
	ID_IP_RECENTLY_CONNECTED, //ip�Ѿ�����

	/// RakPeer - The sizeof(RakNetTime) bytes following this byte represent a value which is automatically modified by the difference
	/// in system times between the sender and the recipient. Requires that you call SetOccasionalPing.
	ID_TIMESTAMP, //ʱ���

    /// RakPeer - Pong from an unconnected system.  First byte is ID_UNCONNECTED_PONG, second sizeof(RakNet::TimeMS) bytes is the ping,
	/// following bytes is system specific enumeration data.
	/// Read using bitstreams
	ID_UNCONNECTED_PONG, //�Ͽ�pong

	/// RakPeer - Inform a remote system of our IP/Port. On the recipient, all data past ID_ADVERTISE_SYSTEM is whatever was passed to
	/// the data parameter
	ID_ADVERTISE_SYSTEM,//����ϵͳ

	// RakPeer - Downloading a large message. Format is ID_DOWNLOAD_PROGRESS (MessageID), partCount (unsigned int),
	///  partTotal (unsigned int),
	/// partLength (unsigned int), first part data (length <= MAX_MTU_SIZE). See the three parameters partCount, partTotal
	///  and partLength in OnFileProgress in FileListTransferCBInterface.h
	ID_DOWNLOAD_PROGRESS, //���ؽ���
	
	/// ConnectionGraph2 plugin - In a client/server environment, a client other than ourselves has disconnected gracefully.
	///   Packet::systemAddress is modified to reflect the systemAddress of this client.
	ID_REMOTE_DISCONNECTION_NOTIFICATION, //Զ��ϵͳ�Ͽ�֪ͨ

	/// ConnectionGraph2 plugin - In a client/server environment, a client other than ourselves has been forcefully dropped.
	///  Packet::systemAddress is modified to reflect the systemAddress of this client.
	ID_REMOTE_CONNECTION_LOST, //Զ��ϵͳ���Ӷ�ʧ

	/// ConnectionGraph2 plugin: Bytes 1-4 = count. for (count items) contains {SystemAddress, RakNetGUID, 2 byte ping}
	ID_REMOTE_NEW_INCOMING_CONNECTION, //��Զ������

	/// FileListTransfer plugin - Setup data
	ID_FILE_LIST_TRANSFER_HEADER, //�ļ�����ͷ��Ϣ

	/// FileListTransfer plugin - A file
	ID_FILE_LIST_TRANSFER_FILE, //�ļ����� �ļ�

	// Ack for reference push, to send more of the file
	ID_FILE_LIST_REFERENCE_PUSH_ACK, //���͸�����ļ�

	/// DirectoryDeltaTransfer plugin - Request from a remote system for a download of a directory
	ID_DDT_DOWNLOAD_REQUEST, //��������
	
	/// RakNetTransport plugin - Transport provider message, used for remote console
	ID_TRANSPORT_STRING, //��Ϣ

 	/// ReplicaManager plugin - Create an object
	ID_REPLICA_MANAGER_CONSTRUCTION, //���ƹ��� ��������

 	/// ReplicaManager plugin - Changed scope of an object
 	ID_REPLICA_MANAGER_SCOPE_CHANGE, //���ƹ��� �����ı�

 	/// ReplicaManager plugin - Serialized data of an object
	ID_REPLICA_MANAGER_SERIALIZE, //���ƹ��� �����ʼ��

 	/// ReplicaManager plugin - New connection, about to send all world objects
	ID_REPLICA_MANAGER_DOWNLOAD_STARTED, //���ƹ��� 

 	/// ReplicaManager plugin - Finished downloading all serialized objects
	ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE, //���ƹ��� ���

	/// RakVoice plugin - Open a communication channel
	ID_RAKVOICE_OPEN_CHANNEL_REQUEST, //�������

	/// RakVoice plugin - Communication channel accepted
	ID_RAKVOICE_OPEN_CHANNEL_REPLY, //ͨ���ظ�

	/// RakVoice plugin - Close a communication channel
	ID_RAKVOICE_CLOSE_CHANNEL, //�ر�ͨ��

	/// RakVoice plugin - Voice data
	ID_RAKVOICE_DATA, //��������

	/// Autopatcher plugin - Get a list of files that have changed since a certain date
	ID_AUTOPATCHER_GET_CHANGELIST_SINCE_DATE, //���²��

	/// Autopatcher plugin - A list of files to create
	ID_AUTOPATCHER_CREATION_LIST,//���²��

	/// Autopatcher plugin - A list of files to delete
	ID_AUTOPATCHER_DELETION_LIST,//���²��

	/// Autopatcher plugin - A list of files to get patches for
	ID_AUTOPATCHER_GET_PATCH,//���²��

	/// Autopatcher plugin - A list of patches for a list of files
	ID_AUTOPATCHER_PATCH_LIST,//���²��

	/// Autopatcher plugin - Returned to the user: An error from the database repository for the autopatcher.
	ID_AUTOPATCHER_REPOSITORY_FATAL_ERROR,//���²��

	/// Autopatcher plugin - Returned to the user: The server does not allow downloading unmodified game files.
	ID_AUTOPATCHER_CANNOT_DOWNLOAD_ORIGINAL_UNMODIFIED_FILES,//���²��

	/// Autopatcher plugin - Finished getting all files from the autopatcher
	ID_AUTOPATCHER_FINISHED_INTERNAL,//���²��

	ID_AUTOPATCHER_FINISHED,//���²��

	/// Autopatcher plugin - Returned to the user: You must restart the application to finish patching.
	ID_AUTOPATCHER_RESTART_APPLICATION,//���²��

	/// NATPunchthrough plugin: internal
	ID_NAT_PUNCHTHROUGH_REQUEST, //��͸

	/// NATPunchthrough plugin: internal
	//ID_NAT_GROUP_PUNCHTHROUGH_REQUEST,//��͸

	/// NATPunchthrough plugin: internal
	//ID_NAT_GROUP_PUNCHTHROUGH_REPLY,//��͸

	/// NATPunchthrough plugin: internal
	ID_NAT_CONNECT_AT_TIME, //��͸ʱ��

	/// NATPunchthrough plugin: internal
	ID_NAT_GET_MOST_RECENT_PORT, //��ȡ����Ķ˿�

	/// NATPunchthrough plugin: internal
	ID_NAT_CLIENT_READY, //��͸��׼��

	/// NATPunchthrough plugin: internal
	//ID_NAT_GROUP_PUNCHTHROUGH_FAILURE_NOTIFICATION,

	/// NATPunchthrough plugin: Destination system is not connected to the server. Bytes starting at offset 1 contains the
	///  RakNetGUID destination field of NatPunchthroughClient::OpenNAT().
	ID_NAT_TARGET_NOT_CONNECTED, //��͸ Ŀ��δ����

	/// NATPunchthrough plugin: Destination system is not responding to ID_NAT_GET_MOST_RECENT_PORT. Possibly the plugin is not installed.
	///  Bytes starting at offset 1 contains the RakNetGUID  destination field of NatPunchthroughClient::OpenNAT().
	ID_NAT_TARGET_UNRESPONSIVE, //��͸ Ŀ��δ��Ӧ

	/// NATPunchthrough plugin: The server lost the connection to the destination system while setting up punchthrough.
	///  Possibly the plugin is not installed. Bytes starting at offset 1 contains the RakNetGUID  destination
	///  field of NatPunchthroughClient::OpenNAT().
	ID_NAT_CONNECTION_TO_TARGET_LOST,//��͸ Ŀ�궪ʧ

	/// NATPunchthrough plugin: This punchthrough is already in progress. Possibly the plugin is not installed.
	///  Bytes starting at offset 1 contains the RakNetGUID destination field of NatPunchthroughClient::OpenNAT().
	ID_NAT_ALREADY_IN_PROGRESS,//��͸ ͨѶ��

	/// NATPunchthrough plugin: This message is generated on the local system, and does not come from the network.
	///  packet::guid contains the destination field of NatPunchthroughClient::OpenNAT(). Byte 1 contains 1 if you are the sender, 0 if not
	ID_NAT_PUNCHTHROUGH_FAILED, //��͸ ʧ��

	/// NATPunchthrough plugin: Punchthrough succeeded. See packet::systemAddress and packet::guid. Byte 1 contains 1 if you are the sender,
	///  0 if not. You can now use RakPeer::Connect() or other calls to communicate with this system.
	ID_NAT_PUNCHTHROUGH_SUCCEEDED, //��͸ �ɹ�

	/// ReadyEvent plugin - Set the ready state for a particular system
	/// First 4 bytes after the message contains the id
	ID_READY_EVENT_SET, //�Ѿ�׼��

	/// ReadyEvent plugin - Unset the ready state for a particular system
	/// First 4 bytes after the message contains the id
	ID_READY_EVENT_UNSET, //δ׼��

	/// All systems are in state ID_READY_EVENT_SET
	/// First 4 bytes after the message contains the id
	ID_READY_EVENT_ALL_SET, //ȫ��׼��

	/// \internal, do not process in your game
	/// ReadyEvent plugin - Request of ready event state - used for pulling data when newly connecting
	ID_READY_EVENT_QUERY, //׼���¼���ѯ

	/// Lobby packets. Second byte indicates type.
	ID_LOBBY_GENERAL, //����

	// RPC3, RPC4 error
	ID_RPC_REMOTE_ERROR, //rpcԶ�̴���

	/// Plugin based replacement for RPC system
	ID_RPC_PLUGIN, //rpcϵͳ

	/// FileListTransfer transferring large files in chunks that are read only when needed, to save memory
	ID_FILE_LIST_REFERENCE_PUSH, //�ļ��б���

	/// Force the ready event to all set
	ID_READY_EVENT_FORCE_ALL_SET, //ǿ��׼���¼�

	/// Rooms function ���书��
	ID_ROOMS_EXECUTE_FUNC, //ִ��
	ID_ROOMS_LOGON_STATUS, //��½״̬
	ID_ROOMS_HANDLE_CHANGE, //����ı�

	/// Lobby2 message
	ID_LOBBY2_SEND_MESSAGE, //������Ϣ

	ID_LOBBY2_SERVER_ERROR,//�����������

	/// Informs user of a new host GUID. Packet::Guid contains this new host RakNetGuid. The old host can be read out using BitStream->Read(RakNetGuid) starting on byte 1
	/// This is not returned until connected to a remote system
	/// If the oldHost is UNASSIGNED_RAKNET_GUID, then this is the first time the host has been determined
	ID_FCM2_NEW_HOST, //�������Ӳ�� �µ�����

	/// \internal For FullyConnectedMesh2 plugin
	ID_FCM2_REQUEST_FCMGUID,//�������Ӳ�� ����id

	/// \internal For FullyConnectedMesh2 plugin
	ID_FCM2_RESPOND_CONNECTION_COUNT, //�������Ӳ�� �������Ӹ���

	/// \internal For FullyConnectedMesh2 plugin
	ID_FCM2_INFORM_FCMGUID, //�������Ӳ�� id

	/// \internal For FullyConnectedMesh2 plugin
	ID_FCM2_UPDATE_MIN_TOTAL_CONNECTION_COUNT, //�������Ӳ�� ������С���Ӹ���

	/// A remote system (not necessarily the host) called FullyConnectedMesh2::StartVerifiedJoin() with our system as the client
	/// Use FullyConnectedMesh2::GetVerifiedJoinRequiredProcessingList() to read systems
	/// For each system, attempt NatPunchthroughClient::OpenNAT() and/or RakPeerInterface::Connect()
	/// When this has been done for all systems, the remote system will automatically be informed of the results
	/// \note Only the designated client gets this message
	/// \note You won't get this message if you are already connected to all target systems
	/// \note If you fail to connect to a system, this does not automatically mean you will get ID_FCM2_VERIFIED_JOIN_FAILED as that system may have been shutting down from the host too
	/// \sa FullyConnectedMesh2::StartVerifiedJoin()
	ID_FCM2_VERIFIED_JOIN_START, //��ʼ��֤����

	/// \internal The client has completed processing for all systems designated in ID_FCM2_VERIFIED_JOIN_START
	ID_FCM2_VERIFIED_JOIN_CAPABLE, //����֤����

	/// Client failed to connect to a required systems notified via FullyConnectedMesh2::StartVerifiedJoin()
	/// RakPeerInterface::CloseConnection() was automatically called for all systems connected due to ID_FCM2_VERIFIED_JOIN_START 
	/// Programmer should inform the player via the UI that they cannot join this session, and to choose a different session
	/// \note Server normally sends us this message, however if connection to the server was lost, message will be returned locally
	/// \note Only the designated client gets this message
	ID_FCM2_VERIFIED_JOIN_FAILED, //��֤���� ʧ��

	/// The system that called StartVerifiedJoin() got ID_FCM2_VERIFIED_JOIN_CAPABLE from the client and then called RespondOnVerifiedJoinCapable() with true
	/// AddParticipant() has automatically been called for this system
	/// Use GetVerifiedJoinAcceptedAdditionalData() to read any additional data passed to RespondOnVerifiedJoinCapable()
	/// \note All systems in the mesh get this message
	/// \sa RespondOnVerifiedJoinCapable()
	ID_FCM2_VERIFIED_JOIN_ACCEPTED, //��֤���� ����

	/// The system that called StartVerifiedJoin() got ID_FCM2_VERIFIED_JOIN_CAPABLE from the client and then called RespondOnVerifiedJoinCapable() with false
	/// CloseConnection() has been automatically called for each system connected to since ID_FCM2_VERIFIED_JOIN_START.
	/// The connection is NOT automatically closed to the original host that sent StartVerifiedJoin()
	/// Use GetVerifiedJoinRejectedAdditionalData() to read any additional data passed to RespondOnVerifiedJoinCapable()
	/// \note Only the designated client gets this message
	/// \sa RespondOnVerifiedJoinCapable()
	ID_FCM2_VERIFIED_JOIN_REJECTED, //��֤���� �ܾ�

	/// UDP proxy messages. Second byte indicates type.
	ID_UDP_PROXY_GENERAL, //udp������Ϣ���ڶ��ֽ� ����

	/// SQLite3Plugin - execute
	ID_SQLite3_EXEC, //Զ�����ݿ�ִ��

	/// SQLite3Plugin - Remote database is unknown
	ID_SQLite3_UNKNOWN_DB, //δ֪���ݿ�

	/// Events happening with SQLiteClientLoggerPlugin
	ID_SQLLITE_LOGGER, //��־���

	/// Sent to NatTypeDetectionServer
	ID_NAT_TYPE_DETECTION_REQUEST, //ƥ����������

	/// Sent to NatTypeDetectionClient. Byte 1 contains the type of NAT detected.
	ID_NAT_TYPE_DETECTION_RESULT, //������������ƥ��ͻ��� ��һ�ֽڰ�������

	/// Used by the router2 plugin
	ID_ROUTER_2_INTERNAL, //·�������

	/// No path is available or can be established to the remote system
	/// Packet::guid contains the endpoint guid that we were trying to reach
	ID_ROUTER_2_FORWARDING_NO_PATH, //�޷������Է�

	/// \brief You can now call connect, ping, or other operations to the destination system.
	///
	/// Connect as follows:
	///
	/// RakNet::BitStream bs(packet->data, packet->length, false);
	/// bs.IgnoreBytes(sizeof(MessageID));
	/// RakNetGUID endpointGuid;
	/// bs.Read(endpointGuid);
	/// unsigned short sourceToDestPort;
	/// bs.Read(sourceToDestPort);
	/// char ipAddressString[32];
	/// packet->systemAddress.ToString(false, ipAddressString);
	/// rakPeerInterface->Connect(ipAddressString, sourceToDestPort, 0,0);
	ID_ROUTER_2_FORWARDING_ESTABLISHED, //�����Ѿ���������

	/// The IP address for a forwarded connection has changed
	/// Read endpointGuid and port as per ID_ROUTER_2_FORWARDING_ESTABLISHED
	ID_ROUTER_2_REROUTED, //������ip��ַ�����ı�

	/// \internal Used by the team balancer plugin
	ID_TEAM_BALANCER_INTERNAL, //�Ŷ�ƽ����

	/// Cannot switch to the desired team because it is full. However, if someone on that team leaves, you will
	///  get ID_TEAM_BALANCER_TEAM_ASSIGNED later.
	/// For TeamBalancer: Byte 1 contains the team you requested to join. Following bytes contain NetworkID of which member
	ID_TEAM_BALANCER_REQUESTED_TEAM_FULL, //�Ŷ��Ѿ���

	/// Cannot switch to the desired team because all teams are locked. However, if someone on that team leaves,
	///  you will get ID_TEAM_BALANCER_SET_TEAM later.
	/// For TeamBalancer: Byte 1 contains the team you requested to join.
	ID_TEAM_BALANCER_REQUESTED_TEAM_LOCKED, //�Ŷ� ������
	ID_TEAM_BALANCER_TEAM_REQUESTED_CANCELLED, //�Ŷ� �����ͷ�

	/// Team balancer plugin informing you of your team. Byte 1 contains the team you requested to join. Following bytes contain NetworkID of which member.
	ID_TEAM_BALANCER_TEAM_ASSIGNED, //�Ŷ�ƽ�������  1�ֽڱ�ʶ�������������ֽڱ�ʾ��Ա

	/// Gamebryo Lightspeed integration
	ID_LIGHTSPEED_INTEGRATION, //����

	/// XBOX integration
	ID_XBOX_LOBBY, //��Ϸ����

	/// The password we used to challenge the other system passed, meaning the other system has called TwoWayAuthentication::AddPassword() with the same password we passed to TwoWayAuthentication::Challenge()
	/// You can read the identifier used to challenge as follows:
	/// RakNet::BitStream bs(packet->data, packet->length, false); bs.IgnoreBytes(sizeof(RakNet::MessageID)); RakNet::RakString password; bs.Read(password);
	ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_SUCCESS,//˫����֤�ɹ������գ�
	ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_SUCCESS,//˫����֤�ɹ�������

	/// A remote system sent us a challenge using TwoWayAuthentication::Challenge(), and the challenge failed.
	/// If the other system must pass the challenge to stay connected, you should call RakPeer::CloseConnection() to terminate the connection to the other system. 
	ID_TWO_WAY_AUTHENTICATION_INCOMING_CHALLENGE_FAILURE,//˫����֤ʧ�ܣ����գ�

	/// The other system did not add the password we used to TwoWayAuthentication::AddPassword()
	/// You can read the identifier used to challenge as follows:
	/// RakNet::BitStream bs(packet->data, packet->length, false); bs.IgnoreBytes(sizeof(MessageID)); RakNet::RakString password; bs.Read(password);
	ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_FAILURE, //˫����֤ʧ�ܣ�����

	/// The other system did not respond within a timeout threshhold. Either the other system is not running the plugin or the other system was blocking on some operation for a long time.
	/// You can read the identifier used to challenge as follows:
	/// RakNet::BitStream bs(packet->data, packet->length, false); bs.IgnoreBytes(sizeof(MessageID)); RakNet::RakString password; bs.Read(password);
	ID_TWO_WAY_AUTHENTICATION_OUTGOING_CHALLENGE_TIMEOUT, //˫����֤��ʱ������

	/// \internal �ڲ�
	ID_TWO_WAY_AUTHENTICATION_NEGOTIATION, //˫����֤

	/// CloudClient / CloudServer �ƶ�/�Ʒ�����
	ID_CLOUD_POST_REQUEST,
	ID_CLOUD_RELEASE_REQUEST,
	ID_CLOUD_GET_REQUEST,
	ID_CLOUD_GET_RESPONSE,
	ID_CLOUD_UNSUBSCRIBE_REQUEST,
	ID_CLOUD_SERVER_TO_SERVER_COMMAND,
	ID_CLOUD_SUBSCRIPTION_NOTIFICATION,

	// LibVoice 
	ID_LIB_VOICE, //����

	ID_RELAY_PLUGIN, //�ָ����

	ID_NAT_REQUEST_BOUND_ADDRESSES, //�����ַ

	ID_NAT_RESPOND_BOUND_ADDRESSES, //�ظ���ַ

	ID_FCM2_UPDATE_USER_CONTEXT, //�����û�

	ID_RESERVED_3,
	ID_RESERVED_4,
	ID_RESERVED_5,
	ID_RESERVED_6,
	ID_RESERVED_7,
	ID_RESERVED_8,
	ID_RESERVED_9,

	// For the user to use.  Start your first enumeration at this value.
	ID_USER_PACKET_ENUM
	//-------------------------------------------------------------------------------------------------------------
 
};

#endif // RAKNET_USE_CUSTOM_PACKET_IDS

#endif