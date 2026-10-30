// 题目：953. 验证外星语词典（Verifying an Alien Dictionary）
// 思路：先用 order 建「字母 → 字典序排名」的映射，再逐对比较相邻单词：找到第一处不同就比排名，完全相同则要求是前缀关系（短的在前面）。
// 时间复杂度：O(总字符数)，每个单词只扫一遍；空间复杂度：O(1)，26 个元素的定长映射表。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 宏定义取较小值，用于比较两个单词的公共前缀长度

bool isAlienSorted(char** words, int wordsSize, char* order) {  // words：按外星语排序的单词表；wordsSize：单词个数；order：外星语字母表
    int map[26] = {0};  // map[c] 记录字母 c 在外星语中的排名（0 表示最小）
    for (int i = 0; i < 26; i++) {  // 遍历字母表 order 的每一位
        map[order[i] - 'a'] = i;  // 把字母映射成它的排名；减去 'a' 把字符变成 0-25 的下标
    }
    for (int i = 1; i < wordsSize; i++) {  // 从第二个单词开始，与它的前一个单词比较
        char* s1 = words[i - 1];  // 前一个单词
        char* s2 = words[i];  // 当前单词
        int n = strlen(s1);  // 前一个单词的长度
        int m = strlen(s2);  // 当前单词的长度
        int len = min(n, m);  // 只需要比较到公共前缀的长度
        int isEqual = 1;  // 标记公共前缀部分是否完全相等，1 表示相等
        for (int j = 0; j < len; j++) {  // 逐字符比较公共前缀
            if (map[s1[j] - 'a'] > map[s2[j] - 'a']) {  // 前一个单词当前的字母排名更大，说明顺序被破坏
                return 0;  // 直接判定不是外星语有序
            }
            if (map[s1[j] - 'a'] < map[s2[j] - 'a']) {  // 前一个单词当前的字母排名更小，顺序已经确定
                isEqual = 0;  // 公共前缀不再全等
                break;  // 后面无需再比较，退出内层循环
            }
        }
        if (isEqual && n > m) {  // 公共前缀相同却出现「长的在前」，不符合字典序
            return 0;  // 同样判定不合法
        }
    }
    return 1;  // 所有相邻单词对都满足顺序要求
}  // 返回 1 表示是合法排序