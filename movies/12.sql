select b.title
from stars a,movies b,people c
where a.movie_id =b.id
and a.person_id = c.id
and c.name in ("Johnny Depp" ,"Helena Bonham Carter")
group by a.movie_id
having count(*)=2