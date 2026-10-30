// 题目：2399. 检查相同字母间的距离（Check Distances Between Same Letters）
// 思路：数组记录每个字母首次出现的位置（存 i+1 以区分“未出现”），再次出现时校验中间字符数是否等于 distance。
// 时间复杂度：O(n)，只扫描字符串一遍；空间复杂度：O(1)，固定 26 个槽位的计数数组。
bool checkDistances(char* s, int* distance, int distanceSize) {  // s：待检查字符串；distance：每个字母规定的间隔；返回是否全部符合
    int n = strlen(s);  // 字符串长度，用于控制扫描范围
    int d[26] = {0};  // d[j] 记录字母 j 首次出现的下标 + 1，0 表示还没出现过
    for (int i = 0; i < n; i++) {  // 从左到右扫描每个字符
        int j = s[i] - 'a';  // 把字符映射到 0..25 的字母序号
        if (d[j] > 0 && i - d[j] != distance[j]) {  // 之前出现过，且两次下标差减 1（中间字符数）不等于规定距离
            return false;  // 距离不符，直接判定失败
        }
        d[j] = i + 1;  // 记录当前位置（加 1，避免与“未出现”的 0 混淆，也顺带覆盖最新位置）
    }
    return true;  // 所有字母的距离都符合要求，返回 true
}