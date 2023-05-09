#ifndef ICOMMAND_RECORDER_H
#define ICOMMAND_RECORDER_H

#include "./ICommand.h"

typedef struct CommandRecorder CommandRecorder;

CommandRecorder* CommandRecorder_new(int history_size);
void CommandRecorder_destroy(CommandRecorder* self);

void CommandRecorder_record(CommandRecorder* self, ICommand* command);

void CommandRecorder_redo(CommandRecorder* self, int redo_count);
void CommandRecorder_undo(CommandRecorder* self, int undo_count);

#endif