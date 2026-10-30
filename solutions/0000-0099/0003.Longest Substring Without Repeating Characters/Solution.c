// 题目：3. 无重复字符的最长子串（Longest Substring Without Repeating Characters）
// 思路：滑动窗口 + 计数数组，右指针不断扩张；一旦窗口内某字符重复，就移动左指针收缩到重新合法为止。
// 时间复杂度：O(n)，每个下标最多被左右指针各扫过一次；空间复杂度：O(1)，字符集大小固定为 256。
int lengthOfLongestSubstring(char* s) {  // s 为输入字符串，返回无重复字符的最长子串长度
    int freq[256] = {0};  // 计数器：freq[c] 为字符 c 在当前窗口内出现的次数，初值全 0
    int l = 0, r = 0;  // 滑动窗口的左右边界（左闭右闭）
    int ans = 0;  // 记录窗口长度的历史最大值
    int len = strlen(s);  // 提前求长度，避免循环中反复调用 strlen

    for (r = 0; r < len; r++) {  // 右指针从左到右扩张窗口
        char c = s[r];  // 刚进入窗口的字符
        freq[(unsigned char) c]++;  // 该字符在窗口内的出现次数加一（转无符号，避免负字符做下标）

        while (freq[(unsigned char) c] > 1) {  // c 出现两次，窗口失效，需要收缩左边界
            freq[(unsigned char) s[l]]--;  // 左边界字符移出窗口，计数减一
            l++;  // 左指针右移
        }

        if (ans < r - l + 1) {  // 当前窗口长度为 r - l + 1，若更大就更新
            ans = r - l + 1;  // 更新最长长度
        }
    }

    return ans;  // 返回最长合法窗口的长度
}
