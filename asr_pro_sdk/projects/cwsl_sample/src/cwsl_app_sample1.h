#ifndef __CWSL_APP_SAMPLE1_H__
#define __CWSL_APP_SAMPLE1_H__

#include "system_msg_deal.h"
#include "cwsl_manage.h"


typedef enum
{
    CWSL_REGISTRATION_WAKE          = 400,      ///< 命令词：学习唤醒词
    CWSL_REGISTRATION_CMD           = 401,      ///< 命令词：学习命令词
    CWSL_REGISTER_AGAIN             = 402,      ///< 命令词：重新学习
    CWSL_EXIT_REGISTRATION          = 403,      ///< 命令词：退出学习
    CWSL_DELETE_FUNC                = 404,      ///< 命令词：我要删除
    CWSL_DELETE_WAKE                = 405,      ///< 命令词：删除唤醒词
    CWSL_DELETE_CMD                 = 406,      ///< 命令词：删除命令词
    CWSL_EXIT_DELETE                = 407,      ///< 命令词：退出删除模式
    CWSL_DELETE_ALL                 = 408,      ///< 命令词：全部删除

    CWSL_REGISTRATION_NEXT          = 499,      ///< 播报：学习下一个
    CWSL_DATA_ENTERY_SUCCESSFUL     = 409,      ///< 播报：学习成功
    CWSL_DATA_ENTERY_FAILED         = 410,      ///< 播报：学习失败
    CWSL_REGISTRATION_SUCCESSFUL    = 411,      ///< 播报：学习成功
    CWSL_TEMPLATE_FULL              = 412,      ///< 播报：学习模板超过上限
    CWSL_SPEAK_AGAIN                = 419,     ///< 播报：请再说一次>
    CWSL_TOO_SHORT                  = 420,     ///< 播报：语音长度不够，请再说一次>

    CWSL_DELETE_SUCCESSFUL          = 413,      ///< 播报：删除成功
    CWSL_DELETE_FAILED              = 414,      ///< 播报：删除失败
    CWSL_DELETING                   = 415,      ///< 播报：删除中
    CWSL_DONT_FIND_WORD             = 416,      ///< 播报：找不到删除的词
    CWSL_REGISTRATION_ALL           = 417,      ///< 播报：学习完成
    CWSL_REG_FAILED                 = 418,      ///< 播报：学习失败
    CWSL_REG_FAILED_DEFAULT_CMD_CONFLICT = 421, ///< 播报：与默认指令冲突，请换种说法
}cicwsl_func_index;


////cwsl process ASR message///////////////////////////////////////////////
/**
 * @brief 命令词自学习消息处理函数
 * 
 * @param asr_msg ASR识别结果消息
 * @param cmd_handle 命令词handle
 * @param cmd_id 命令词ID
 * @retval 1 数据有效,消息已处理
 * @retval 0 数据无效,消息未处理
 */
uint32_t cwsl_app_process_asr_msg(sys_msg_asr_data_t *asr_msg, cmd_handle_t *cmd_handle, uint16_t cmd_id);

// cwsl_manage模块复位，用于系统退出唤醒状态时调用
int cwsl_app_reset();

#endif  // __CWSL_APP_SAMPLE1_H__
