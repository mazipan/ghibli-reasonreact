open Belt;
open Utils;

requireCSS("src/FilmPage.css");

type state = {
  films: FilmData.films,
  loading: bool,
};

type action =
  | Loaded((FilmData.films))
  | Loading;

let component = ReasonReact.reducerComponent("FilmPage");

let make = _children => {
  ...component,
  initialState: () => {films: [||], loading: false},
  reducer: (action, state) =>
    switch (action) {
    | Loading => ReasonReact.Update({...state, loading: true})
    | Loaded((data)) =>
      ReasonReact.Update({
        films: data,
        loading: false,
      });
    },
  didMount: self => {
    FilmData.fetchFilms(data => self.send(Loaded(data)))
  },
  render: _self =>
    <div className="FilmPage">
    (
      if (Array.length(_self.state.films) > 0) {
        _self.state.films
        ->(
            Array.map((film) =>
              <div
                className="FilmPage_item"
                key=(film.id)>
                { ReasonReact.string("" ++ film.title ++ " ("++  film.release_date ++")") }
              </div>
            )
          )
        ->ReasonReact.array;
      } else {
        ReasonReact.null;
      }
    )
    </div>,
};
