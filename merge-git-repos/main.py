import git
import time
import sys


# git filter-branch --force --prune-empty --index-filter 'git rm -rf --cached --ignore-unmatch *.tar.gz' --tag-name-filter cat -- --all

# for i in range(len(commits)):
#     for j in range(i+1, len(commits)):
#         for res in diff_commits(commits[i], commits[j]):
#             (l, r) = res
#             print(l.message)
#             print(r.message)
#             print('-------')

repo = git.Repo('/home/yee.yi/Workspace/vesoft/test-repo/nebula-v2')


def diff_commits(lhs, rhs):
    res = []
    for l in lhs:
        for r in rhs:
            if l.authored_date == r.authored_date and l.committed_date == r.committed_date and l.author == r.author and l.message == r.message:
                res.append((l, r))
    return res


def iter_branch_commits(b):
    return [c for c in repo.iter_commits(b)]


def cut_commits_by_branch(b):
    cs = iter_branch_commits(b)
    if b == 'graph/master':
        idx = find_sha_idx(cs, '91b4f107')
        return cs[:idx+1]
    elif b == 'storage/master':
        idx = find_sha_idx(cs, 'ec97c12c')
        return cs[:idx+1]
    elif b == 'common/master':
        idx = find_sha_idx(cs, '31500ebb')
        return cs[:idx+1]
    elif b == 'storage':
        idx = find_sha_idx(cs, '36e8fcf1a')
        return cs[:idx+1]
    elif b == 'graph':
        idx = find_sha_idx(cs, '85b54c122')
        return cs[:idx+1]
    elif b == 'common':
        idx = find_sha_idx(cs, '008116938')
        return cs[:idx+1]
    else:
        return []

def extract_branches_history(branches):
    return [(b, c) for b in branches for c in cut_commits_by_branch(b)]


def cmp_commits(x, y):
    if x.committed_date < y.commited_date:
        return True
    if x.authored_date < y.authored_date:
        return True
    return False


def find_sha_idx(commits, sha):
    if sha is None or len(sha) == 0:
        return len(commits)
    for i, commit in enumerate(commits):
        c = commit[1] if isinstance(commit, tuple) else commit
        if sha in c.hexsha:
            return i

    raise ValueError(f"invalid sha: {sha}")


def commits_slice(commits, sha):
    commits.sort(key=lambda x: x[1].committed_date, reverse=True)
    idx = find_sha_idx(commits, sha)
    commits = commits[:idx]
    commits.reverse()
    return commits


def save_failed_commit(commit):
    with open("failed-commit.txt", 'w') as f:
        f.write(commit.hexsha)


def continue_cherry(commits):
    try:
        with open("failed-commit.txt", 'r') as f:
            return commits_slice(commits, f.read())
    except IOError:
            return commits_slice(commits, "")


def write_commits(commits):
    # Fri Sep 7 10:51:26 2018
    # time.asctime(time.localtime(c.committed_date)), int(c.committer_tz_offset/60/60
    with open('commits.txt', 'w') as f:
        for co in commits:
            b, c = co[0], co[1]
            f.write("{} {} {} {}({}) {}({}) {}\n".format(
                c.hexsha, c.authored_datetime, c.committed_datetime, c.author.name, b, c.committer.name, c.committer.email, c.summary))


def merge_commits(commits):
    for commit in commits:
        c = commit[1]
        try:
            print('cherry pick {} authored by {} date: {}, summary: {}'.format(c.hexsha, c.author.name,
                                                                               c.authored_datetime, c.summary))

            with repo.git.custom_environment(GIT_AUTHOR_NAME=f"{c.author.name}",
                                             GIT_AUTHOR_EMAIL=f"{c.author.email}",
                                             GIT_AUTHOR_DATE=f"{c.authored_datetime}",
                                             GIT_COMMITTER_DATE=f"{c.committed_datetime}",
                                             GIT_COMMITTER_NAME=f"{c.committer.name}",
                                             GIT_COMMITTER_EMAIL=f"{c.committer.email}"):
                repo.git.execute(['git', 'cherry-pick', c.hexsha])
                repo.git.execute(['git', 'commit', '--amend', '--no-edit'])
        except BaseException as e:
            # with repo.git.custom_environment(GIT_AUTHOR_DATE=f"{c.authored_datetime}", GIT_COMMITTER_DATE=f"{c.committed_datetime}"):
            #     repo.git.execute(['git', 'checkout', '--theirs', '.'])
            #     repo.git.execute(['git', 'cherry-pick', '--continue'])
            if 'nothing to commit, working tree clean' in str(e):
                continue
            else:
                print(e)
                print(f'GIT_AUTHOR_NAME="{c.author.name}" GIT_AUTHOR_EMAIL="{c.author.email}" GIT_AUTHOR_DATE="{c.authored_datetime}" GIT_COMMITTER_NAME="{c.committer.name}" GIT_COMMITTER_EMAIL="{c.committer.email}" GIT_COMMITTER_DATE="{c.committed_datetime}" git cherry-pick --continue')
                save_failed_commit(c)
                return



if __name__ == "__main__":
    # branches = ['graph/master', 'storage/master', 'common/master']
    branches = ['graph', 'storage', 'common']
    commits = extract_branches_history(branches)
    commits = continue_cherry(commits)
    # write_commits(commits)
    merge_commits(commits)
