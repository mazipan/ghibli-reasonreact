

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


let read_film = (json) => {
    let id = Json.Decode.(json |> field("id", string));
    let staticData = Utils.Data.getAdditionalData(id);
    Json.Decode.{
      id,
      title: json |> field("title", string),
      description: json |> field("description", string),
      director: json |> field("director", string),
      producer: json |> field("producer", string),
      release_date: json |> field("release_date", string),
      rt_score: json |> field("rt_score", string),
      imdb: Some(staticData.imdb),
      image: Some(staticData.image),
      streaming: Some(staticData.streaming)
    }
};

let read_films_response = Json.Decode.list(read_film);

