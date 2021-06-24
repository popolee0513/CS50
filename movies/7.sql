select b.title,a.rating
from ratings a ,movies b
where a.movie_id=b.id
and b.year=2010 and a.rating is not null
order by a.rating desc, b.title asc