# 3485. 删除元素后 K 个字符串的最长公共前缀 / Longest Common Prefix of K Strings After Removal
# 核心思路：用字典树统计每个前缀被多少单词共享；线段树按深度维护“计数仍 >= k 的前缀数 > 0”的最大深度，逐个单词临时撤销其恰好被 k 个单词共享的深度并查询，最后恢复现场。
# 复杂度：时间 O(total_len + L log L)（L 为最大可用前缀长度），空间 O(total_len)。
class Solution:  # 定义题解类
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:  # 主函数：返回每个单词删除后的最长公共前缀长度
        n = len(words)  # 单词个数
        ans = [0] * n  # 记录每个下标删除后的答案，初始为 0
        if n - 1 < k:  # 剩余单词不足 k 个，无法凑出 k 个字符串
            return ans  # 直接返回全 0

        trie = [{'count': 0, 'depth': 0, 'children': [-1] * 26}]  # 字典树：0 号节点为根，children 存子节点下标（-1 表示无）
        for word in words:  # 把所有单词插入字典树以统计前缀出现次数
            cur = 0  # 从根节点出发
            for c in word:  # 逐字符沿树向下走
                idx = ord(c) - 97  # 字符映射到 0..25
                if trie[cur]['children'][idx] == -1:  # 该字母对应的子节点还不存在
                    trie[cur]['children'][idx] = len(trie)  # 新节点下标就是当前字典树的长度
                    trie.append(  # 追加一个新节点
                        {  # 新节点的三个字段
                            'count': 0,  # 该前缀出现次数初始为 0
                            'depth': trie[cur]['depth'] + 1,  # 深度为父节点深度加一，即前缀长度
                            'children': [-1] * 26,  # 初始没有子节点
                        }  # 结束新节点构造
                    )  # 结束 append 调用
                cur = trie[cur]['children'][idx]  # 走向该字符对应的子节点
                trie[cur]['count'] += 1  # 该前缀的出现次数加一

        max_depth = 0  # 仍有至少 k 个单词共享的最大前缀长度
        for i in range(1, len(trie)):  # 遍历所有非根节点
            if trie[i]['count'] >= k:  # 该前缀被至少 k 个单词共享
                max_depth = max(max_depth, trie[i]['depth'])  # 用它更新最大前缀长度

        global_count = [0] * (max_depth + 1)  # 各深度上“计数仍 >= k 的前缀”个数
        for i in range(1, len(trie)):  # 再次遍历所有非根节点
            node = trie[i]  # 取出当前节点
            if node['count'] >= k and node['depth'] <= max_depth:  # 只统计深度不超过最大可用深度的前缀
                global_count[node['depth']] += 1  # 该深度可用前缀数加一

        fragile_list = [[] for _ in range(n)]  # 每个单词删除后会让计数从 k 变成 k-1 的深度列表
        for i, word in enumerate(words):  # 逐个单词收集敏感深度
            cur = 0  # 从根节点开始
            for c in word:  # 沿该单词的字符向下走
                idx = ord(c) - 97  # 字符映射到 0..25
                cur = trie[cur]['children'][idx]  # 走向对应子节点
                if trie[cur]['count'] == k:  # 恰好 k 个单词共享该前缀，删除本单词后它就不再可用
                    fragile_list[i].append(trie[cur]['depth'])  # 记录这个受影响的深度

        seg_size = max_depth  # 线段树维护的深度范围就是最大可用深度
        if seg_size < 1:  # 没有可用深度，无需建树
            return ans  # 答案全为 0，直接返回

        tree = [-1] * (4 * (seg_size + 1))  # 线段树数组，值 -1 表示该深度没有可用前缀

        def build(idx: int, l: int, r: int) -> None:  # 建树：idx 为节点编号，[l, r] 为对应深度区间
            if l == r:  # 区间只剩一个深度，即叶子节点
                tree[idx] = l if global_count[l] > 0 else -1  # 该深度仍有可用前缀则记录深度本身，否则记 -1
                return  # 叶子处理完毕，返回
            mid = (l + r) // 2  # 取区间中点
            build(idx * 2, l, mid)  # 递归建左子树
            build(idx * 2 + 1, mid + 1, r)  # 递归建右子树
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1])  # 父节点取左右儿子的较大值

        def update(idx: int, l: int, r: int, pos: int, new_val: int) -> None:  # 单点更新：把深度 pos 的可用数量改为 new_val
            if l == r:  # 到达叶子节点
                tree[idx] = l if new_val > 0 else -1  # 按新数量决定该深度是否可用
                return  # 叶子更新完毕，返回
            mid = (l + r) // 2  # 取区间中点
            if pos <= mid:  # 目标深度落在左半边
                update(idx * 2, l, mid, pos, new_val)  # 递归更新左子树
            else:  # 目标深度落在右半边
                update(idx * 2 + 1, mid + 1, r, pos, new_val)  # 递归更新右子树
            tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1])  # 回溯更新父节点的最大值

        build(1, 1, seg_size)  # 从根开始建树
        for i in range(n):  # 逐个计算删除该单词后的答案
            for d in fragile_list[i]:  # 先撤销本单词带来的失效深度
                update(1, 1, seg_size, d, global_count[d] - 1)  # 该深度的可用前缀数减一
            res = tree[1]  # 根节点保存整个区间内的最大可用深度
            ans[i] = 0 if res == -1 else res  # -1 表示没有任何可用前缀，答案记为 0
            for d in fragile_list[i]:  # 恢复现场
                update(1, 1, seg_size, d, global_count[d])  # 该深度的可用前缀数复原
        return ans  # 返回每个下标删除后的答案
