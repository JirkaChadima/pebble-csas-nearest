#include <main.h>

void message_callbacks_register(void (*callback)(Place place));

void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);
void inbox_received_callback(DictionaryIterator *iterator, void *context);