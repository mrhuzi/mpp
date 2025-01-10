/*
 * Copyright 2015 Rockchip Electronics Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MPP_TRIE_H__
#define __MPP_TRIE_H__

#include "rk_type.h"
#include "mpp_err.h"

typedef void* MppTrie;

#define MPP_TRIE_KEY_LEN                (4)
#define MPP_TRIE_KEY_MAX                (1 << (MPP_TRIE_KEY_LEN))

/*
 * MppTrie node buffer layout
 * +---------------+
 * |  MppTrieImpl  |
 * +---------------+
 * |  MppTrieNodes |
 * +---------------+
 * |  MppTrieInfos |
 * +---------------+
 *
 * MppTrieInfo element layout
 * +---------------+
 * |  MppTrieInfo  |
 * +---------------+
 * |  name string  |
 * +---------------+
 * |  User context |
 * +---------------+
 */
typedef struct MppTrieInfo_t {
    RK_U32      index       : 12;
    RK_U32      ctx_len     : 12;
    RK_U32      str_len     : 8;
} MppTrieInfo;

#ifdef __cplusplus
extern "C" {
#endif

MPP_RET mpp_trie_init(MppTrie *trie, const char *name);
MPP_RET mpp_trie_init_by_root(MppTrie *trie, void *root);
MPP_RET mpp_trie_deinit(MppTrie trie);

/* Add NULL info to mark the last trie entry */
MPP_RET mpp_trie_add_info(MppTrie trie, const char *name, void *ctx, RK_U32 ctx_len);

RK_S32 mpp_trie_get_node_count(MppTrie trie);
RK_S32 mpp_trie_get_info_count(MppTrie trie);
RK_S32 mpp_trie_get_buf_size(MppTrie trie);
void *mpp_trie_get_node_root(MppTrie trie);

static inline const char *mpp_trie_info_name(MppTrieInfo *info)
{
    return (info) ? (const char *)(info + 1) : NULL;
}

static inline void *mpp_trie_info_ctx(MppTrieInfo *info)
{
    return (info) ? (void *)((char *)(info + 1) + info->str_len) : NULL;
}

/* trie lookup function */
MppTrieInfo *mpp_trie_get_info(MppTrie trie, const char *name);
MppTrieInfo *mpp_trie_get_info_first(MppTrie trie);
MppTrieInfo *mpp_trie_get_info_next(MppTrie trie, MppTrieInfo *info);
/* root base lookup function */
MppTrieInfo *mpp_trie_get_info_from_root(void *root, const char *name);

void mpp_trie_dump(MppTrie trie, const char *func);
#define mpp_trie_dump_f(trie)   mpp_trie_dump(trie, __FUNCTION__)

#ifdef __cplusplus
}
#endif

#endif /*__MPP_TRIE_H__*/
