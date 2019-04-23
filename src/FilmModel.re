type film = {
  id: string,
  title: string,
  description: string,
  director: string,
  producer: string,
  release_date: string,
  rt_score: string,
  imdb: option(string),
  image: option(string),
  streaming: option(string)
};

type films = array(film);
