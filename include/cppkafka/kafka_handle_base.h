#ifndef CPPKAFKA_KAFKA_HANDLE_BASE_H
#define CPPKAFKA_KAFKA_HANDLE_BASE_H

#include <string>
#include <memory>
#include <librdkafka/rdkafka.h>
#include "topic_partition_list.h"

namespace cppkafka {

class Topic;
class TopicConfiguration;

class KafkaHandleBase {
public:
    virtual ~KafkaHandleBase() = default;
    KafkaHandleBase(const KafkaHandleBase&) = delete;
    KafkaHandleBase(KafkaHandleBase&&) = delete;
    KafkaHandleBase& operator=(const KafkaHandleBase&) = delete;
    KafkaHandleBase& operator=(KafkaHandleBase&&) = delete;

    void pause_partitions(const TopicPartitionList& topic_partitions);
    void resume_partitions(const TopicPartitionList& topic_partitions);

    rd_kafka_t* get_handle();
    Topic get_topic(const std::string& name);
    Topic get_topic(const std::string& name, TopicConfiguration config);
protected:
    KafkaHandleBase();
    KafkaHandleBase(rd_kafka_t* handle);

    void set_handle(rd_kafka_t* handle);
    void check_error(rd_kafka_resp_err_t error);
private:
    using HandlePtr = std::unique_ptr<rd_kafka_t, decltype(&rd_kafka_destroy)>;

    Topic get_topic(const std::string& name, rd_kafka_topic_conf_t* conf);

    HandlePtr handle_;
};

} // cppkafka

#endif // CPPKAFKA_KAFKA_HANDLE_BASE_H