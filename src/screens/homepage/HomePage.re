open Utils;

requireCSS("src/screens/homepage/HomePage.css");
let placeholderImage = requireAssetURI("src/assets/image/placeholder.png");

let component = ReasonReact.statelessComponent("HomePage");

module GetFilms =
  Get.Make({
    type response = list(Model.film);
  });

let make = _children => {
  ...component,
  render: _self =>
    <div className="FilmPage">
      <GetFilms remoteUrl=Constants.Url.base decoder=Model.read_films_response>
        ...{status =>
          switch (status) {
          | Idle => ReasonReact.null
          | Loading => ReasonReact.string("Loading")
          | Loaded(datas) =>
            if (List.length(datas) > 0) {
              datas->Model.(
                       List.map(
                         ({id, title, image, release_date}) =>
                           <div className="FilmPage__item" key=id>
                             {switch (image) {
                              | Some(image) =>
                                <img
                                  alt=title
                                  src=image
                                  className="FilmPage__item-img"
                                />
                              | None => <img alt=title src=placeholderImage />
                              }}
                             <Link
                               href={"/film/" ++ id}
                               className="FilmPage__item-title">
                               <h2>
                                 {ReasonReact.string(
                                    "" ++ title ++ " (" ++ release_date ++ ")",
                                  )}
                               </h2>
                             </Link>
                           </div>,
                         _,
                       )
                     )
              |> Array.of_list
              |> ReasonReact.array;
            } else {
              ReasonReact.null;
            }
          | Error => ReasonReact.string("error")
          }
        }
      </GetFilms>
    </div>,
};