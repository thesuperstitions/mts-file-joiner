/*---------------------------------------------------------------------------*/
#ifndef __framework__utils__InterprocessQueueH
#define __framework__utils__InterprocessQueueH

/*---------------------------------------------------------------------------*/

#define INTERPROCESS_QUEUE_MAX_MESSAGE_SIZE_IN_BYTES 4096
#define INTERPROCESS_QUEUE_MAX_MESSAGES_IN_QUEUE     1000

typedef void framework_utils_InterprocessQueue;

#ifdef __cplusplus
extern "C" {
#endif

/*   Constructors and destructors    */
framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create(int* result, const char* queueName);
framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create1(int* result, const char* queueName, 
							  	unsigned int maxMessageSizeInBytes);
framework_utils_InterprocessQueue* framework_utils_InterprocessQueue_create2(int* result, const char* queueName, 
									unsigned int maxMessageSizeInBytes, unsigned long int maxNumberOfMessages);

int framework_utils_InterprocessQueue_delete(framework_utils_InterprocessQueue* context);

    /*/*    Operations    /*/
int framework_utils_InterprocessQueue_timedAddMessage(framework_utils_InterprocessQueue* contxt, const unsigned char* message, unsigned int messageSizeInBytes, 
                               unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);

int framework_utils_InterprocessQueue_timedGetMessage(framework_utils_InterprocessQueue* contxt, unsigned char* msg, unsigned int* messageSizeInBytes, 
                               unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);


int framework_utils_InterprocessQueue_getQueueState(framework_utils_InterprocessQueue* contxt);

int framework_utils_InterprocessQueue_flushQueue(framework_utils_InterprocessQueue* contxt);

int framework_utils_InterprocessQueue_waitOnQueueSynchronization(framework_utils_InterprocessQueue* contxt, unsigned int timeoutSecs, unsigned long int timeoutMicroSecs);

int framework_utils_InterprocessQueue_destroyInterprocessQueue(const char* queueName);

#ifdef __cplusplus
}
#endif

/*---------------------------------------------------------------------------*/
#endif
