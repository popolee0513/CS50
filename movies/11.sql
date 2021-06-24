select b.title
from stars a,movies b,people c ,ratings d
where a.movie_id =b.id
and a.person_id = c.id
and a.movie_id =d.movie_id
and c.name="Chadwick Boseman"
order by rating Desc
limit 5