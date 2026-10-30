// 题目：1773. 统计匹配检索规则的物品数量（Count Items Matching a Rule）
// 思路：规则键只有 type/color/name 三种，先把它映射成列下标，再逐项比较该列的值是否等于规则值。
// 时间复杂度：O(n·L)，n 为物品数、L 为字符串比较代价；空间复杂度：O(1)。
int countMatches(char*** items, int itemsSize, int* itemsColSize, char* ruleKey, char* ruleValue) {  // items：物品三元组；itemsSize：物品个数；itemsColSize：每行列数；ruleKey/ruleValue：匹配规则
    int k = strcmp(ruleKey, "type") == 0 ? 0 : strcmp(ruleKey, "color") == 0 ? 1  // 按规则键的字符串确定要比较的列下标
                                                                             : 2;  // 既不是 type 也不是 color，就比较第三列 name
    int res = 0;  // 计数器：满足条件的物品个数
    for (int i = 0; i < itemsSize; i++) {  // 逐个遍历物品
        if (strcmp(items[i][k], ruleValue) == 0) {  // 该物品的第 k 列与规则值相同则算匹配
            res++;  // 匹配成功，计数加一
        }
    }
    return res;  // 返回匹配的物品总数
}  // 函数结束