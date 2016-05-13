/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
//�Զ����¡���ͣ
#ifndef __AUTOPATCHER_PATCH_CONTEXT_H
#define __AUTOPATCHER_PATCH_CONTEXT_H

enum PatchContext
{
	PC_HASH_1_WITH_PATCH, //hashֵ
	PC_HASH_2_WITH_PATCH,
	PC_WRITE_FILE, //д���ļ�
	PC_ERROR_FILE_WRITE_FAILURE, //д���ļ�ʧ��
	PC_ERROR_PATCH_TARGET_MISSING, //Ŀ���ļ���ʧ
	PC_ERROR_PATCH_APPLICATION_FAILURE, //ʧ��
	PC_ERROR_PATCH_RESULT_CHECKSUM_FAILURE, //���ʧ��
	PC_NOTICE_WILL_COPY_ON_RESTART, //֪ͨ���¿���
	PC_NOTICE_FILE_DOWNLOADED, //֪ͨ�ļ�����
	PC_NOTICE_FILE_DOWNLOADED_PATCH, //֪ͨ�ļ����ظ���
};

#endif
