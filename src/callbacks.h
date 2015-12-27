#include <main.h>

void init_callbacks(TextLayer *layer);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);
void inbox_received_callback(DictionaryIterator *iterator, void *context);