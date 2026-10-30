# 题目：609. 在系统中查找重复文件（Find Duplicate File in System）
# 思路：把每条记录按空格拆分，用切片取出括号里的内容作为键，把「目录/文件名」追加到字典的对应列表中。
# 时间复杂度：O(L)，L 为所有字符串总长度；空间复杂度：O(L)，字典保存全部文件路径。
class Solution:  # LeetCode 约定的题解类
    def findDuplicate(self, paths: List[str]) -> List[List[str]]:  # paths 每条是「目录 文件(内容) ...」形式的记录
        d = defaultdict(list)  # 字典：键是文件内容，值是同内容文件的路径列表；默认值自动为列表
        for p in paths:  # 逐条处理一个目录记录
            ps = p.split()  # 按空白切分，ps[0] 是目录，后面各项是「文件名(内容)」
            for f in ps[1:]:  # 从第二项开始才是文件，跳过目录名
                i = f.find('(')  # 找到左括号的位置，用它把文件名和内容分开
                name, content = f[:i], f[i + 1 : -1]  # 左括号前是文件名，左括号后到末尾的右括号前是内容
                d[content].append(ps[0] + '/' + name)  # 按内容分组，保存拼接好的完整路径
        return [v for v in d.values() if len(v) > 1]  # 只保留出现次数大于一的组，即真正的重复文件
