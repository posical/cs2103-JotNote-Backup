/**
 *  CS2103 Special Semester 1 Main Project
 *  Project Group C1
 *
 *  File:   CommandTask.h
 *
 *
 * Copyright (c) 2012, AY11/12 Special Term 1 CS2103 Group C1. All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither our names nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef COMMANDTASK_H
#define COMMANDTASK_H

#define COMMAND_ADD_TASK "add"
#define COMMAND_REMOVE_TASK "rmv"
#define COMMAND_REMOVE_TASK_ID "rmv"
#define COMMAND_MODIFY_TASK "mod"
#define COMMAND_MARK_DONE "done"
#define COMMAND_FIND_SLOT "findslot"
#define COMMAND_SEARCH "search"
#define COMMAND_LIST_HISTORY "hist"
#define COMMAND_UNDO "undo"

#define COMMAND_DUE "-due"
#define COMMAND_SHEDULED "-sch"
#define COMMAND_STARTING_TIME "-from"
#define COMMAND_END_TIME "-to"
#define COMMAND_DETAILS "-d"

#define COMMAND_REMOVE_TASK_BY_NAME "remove by name"
#define COMMAND_REMOVE_TASK_BY_ID "remove by id"

#define DEFAULT -1

#endif /* COMMANDTASK_H */
