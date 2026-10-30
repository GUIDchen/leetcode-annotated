# 题目：3799. 单词方块 II（Word Squares II）
# 思路：单词长度固定为 4，枚举上、左、右、下四条边的单词，只校验四个角上的字符是否两两相等。
# 时间复杂度：O(n^4)，四重循环枚举四条边；空间复杂度：O(1)（不计答案本身占用的空间）。
class Solution:  # LeetCode 约定的题解类
    def wordSquares(self, words: List[str]) -> List[List[str]]:  # 返回由四个长度为 4 的单词拼成的所有单词方块
        words.sort()  # 先排序，使答案整体按字典序排列
        n = len(words)  # 单词总数
        ans = []  # 存放所有合法单词方块
        for i in range(n):  # 枚举第 1 行（上边）的单词
            top = words[i]  # 上边单词
            for j in range(n):  # 枚举第 1 列（左边）的单词
                if j != i:  # 同一个单词不能用两次
                    left = words[j]  # 左边单词
                    for k in range(n):  # 枚举第 3 列（右边）的单词
                        if k != j and k != i:  # 不能和已选的 top、left 重复
                            right = words[k]  # 右边单词
                            for h in range(n):  # 枚举第 4 行（下边）的单词
                                if h != k and h != j and h != i:  # 不能与前三个已选单词重复
                                    bottom = words[h]  # 下边单词
                                    if (  # 四个角上的字符必须两两相等
                                        top[0] == left[0]  # 左上角：top 首字符与 left 首字符相等
                                        and top[3] == right[0]  # 右上角：top 末字符与 right 首字符相等
                                        and bottom[0] == left[3]  # 左下角：bottom 首字符与 left 末字符相等
                                        and bottom[3] == right[3]  # 右下角：bottom 末字符与 right 末字符相等
                                    ):  # 条件判断结束
                                        ans.append([top, left, right, bottom])  # 四角匹配，记录这个方块
        return ans  # 返回全部合法方块
