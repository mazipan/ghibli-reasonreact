open Belt;
open Utils;

requireCSS("src/FilmPage.css");

type state = {
  films: FilmModel.films,
  loading: bool,
};

type action =
  | Loaded((FilmModel.films))
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
    FilmService.fetchFilms(data => self.send(Loaded(data)))
  },
  render: ({ state }) =>
    <div className="FilmPage">
    (
      if (Array.length(state.films) > 0) {
        state.films
        ->(
            Array.map((film) =>
              <div
                className="FilmPage__item"
                key=(film.id)>
                <Link href={"/film/" ++ film.id}>
                  { ReasonReact.string("" ++ film.title ++ " ("++  film.release_date ++")") }
                </Link>
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
