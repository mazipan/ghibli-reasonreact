let apiBaseUrl = "https://ghibliapi.herokuapp.com/films";

type film = {
  id: string,
  title: string,
  description: string,
  director: string,
  producer: string,
  release_date: string,
  rt_score: string,
};

type films = array(film);

module Decode = {
  let film = json: film =>
    Json.Decode.{
      id: json |> field("id", string),
      title: json |> field("title", string),
      description: json |> field("description", string),
      director: json |> field("director", string),
      producer: json |> field("producer", string),
      release_date: json |> field("release_date", string),
      rt_score: json |> field("rt_score", string),
    };
  let films = json: array(film) => Json.Decode.(json |> array(film));
};

let fetchFilms = (callback) =>
  Js.Promise.(
    Fetch.fetch(apiBaseUrl)
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.films
         |> (
          films => {
             callback((films));
             resolve();
           }
         )
       )
    |> ignore
  ); /* TODO: error handling */

