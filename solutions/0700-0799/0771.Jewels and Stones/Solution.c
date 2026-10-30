// 题目：771. 宝石与石头（Jewels and Stones）
// 核心思路：用长度为 128 的桶数组标记哪些字符属于宝石，再统计 stones 中落在桶里的字符个数。
// 时间复杂度 O(|jewels| + |stones|)；空间复杂度 O(1)（字符集大小固定为 128）。
int numJewelsInStones(char* jewels, char* stones) {  // jewels：宝石类型；stones：拥有的石头；返回其中宝石的个数
    int set[128] = {0};  // 桶数组：下标为字符 ASCII 码，值 1 表示属于宝石；{0} 把数组全部清零
    for (int i = 0; jewels[i]; i++) {  // 遍历 jewels，遇到字符串结束符即停止，省掉一次 strlen
        set[jewels[i]] = 1;  // 把该字符标记为宝石
    }  // for 循环结束
    int ans = 0;  // ans 统计宝石个数
    for (int i = 0; stones[i]; i++) {  // 遍历 stones 的每个字符
        set[stones[i]] && ans++;  // 短路求值：是宝石才执行 ans++，一次完成判断与自增
    }  // for 循环结束
    return ans;  // 返回宝石数量
}  // 函数结束